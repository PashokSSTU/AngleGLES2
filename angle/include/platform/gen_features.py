#! /usr/bin/python3

# Copyright 2022 The ANGLE Project Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
#
# gen_features.py:
#  Code generation for ANGLE features.
#  NOTE: don't run this script directly. Run scripts/run_code_generation.py.

from collections import namedtuple
import json
import os
import re
import sys

feature_files = {
    'd3d_features.json': ('D3D', 'FeaturesD3D'),
    'frontend_features.json': ('Frontend', 'FrontendFeatures'),
    'gl_features.json': ('OpenGL', 'FeaturesGL'),
    'mtl_features.json': ('Metal', 'FeaturesMtl'),
    'vk_features.json': ('Vulkan', 'FeaturesVk'),
}
feature_list_header_file = '../../util/angle_features_autogen.h'
feature_list_source_file = '../../util/angle_features_autogen.cpp'

template_header = u"""// GENERATED FILE - DO NOT EDIT.
// Generated by {script_name} using data from {input_file_name}.
//
{description}

#ifndef ANGLE_PLATFORM_{NAME}_H_
#define ANGLE_PLATFORM_{NAME}_H_

#include "platform/Feature.h"

namespace angle
{{

struct {name} : FeatureSetBase
{{
    {name}();
    ~{name}();

{features}
}};

inline {name}::{name}()  = default;
inline {name}::~{name}() = default;

}}  // namespace angle

#endif  // ANGLE_PLATFORM_{NAME}_H_
"""

template_feature = u"""FeatureInfo {var_name} = {{
     "{display_name}", FeatureCategory::{category},
     {description},
     &members, {issue}
}};
"""

template_feature_list_header = u"""// GENERATED FILE - DO NOT EDIT.
// Generated by {script_name} using data from {input_file_name}.
//
// Copyright 2022 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// angle_features_autogen.h: List of ANGLE features to help enable/disable them in tests.

#ifndef ANGLE_SRC_TESTS_TEST_UTILS_ANGLE_FEATURES_AUTOGEN_H_
#define ANGLE_SRC_TESTS_TEST_UTILS_ANGLE_FEATURES_AUTOGEN_H_

#include "util_export.h"

namespace angle
{{
enum class Feature
{{
{features}

    InvalidEnum,
    EnumCount = InvalidEnum,
}};

ANGLE_UTIL_EXPORT extern const char *GetFeatureName(Feature feature);

}}  // namespace angle

#endif  // ANGLE_SRC_TESTS_TEST_UTILS_ANGLE_FEATURES_AUTOGEN_H_
"""

template_feature_enum = u"""{VarName},"""

template_feature_list_source = u"""// GENERATED FILE - DO NOT EDIT.
// Generated by {script_name} using data from {input_file_name}.
//
// Copyright 2022 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// angle_features_autogen.cpp: List of ANGLE features to help enable/disable them in tests.

#include "angle_features_autogen.h"

#include "common/PackedEnums.h"

namespace angle
{{
namespace
{{
constexpr PackedEnumMap<Feature, const char *> kFeatureNames = {{ {{
{features}
}} }};
}}  // anonymous namespace

const char *GetFeatureName(Feature feature)
{{
    return kFeatureNames[feature];
}}

}}  // namespace angle
"""

template_feature_string = u"""{{Feature::{VarName}, "{display_name}"}},"""


def make_camel_case(json_name):
    assert '_' in json_name, 'feature names in the json file are expected to be in snake_case'
    return re.sub('_(.)', lambda m: m.group(1).upper(), json_name)


def make_header_name(class_name):
    return class_name + '_autogen.h'


def main():
    if len(sys.argv) == 2 and sys.argv[1] == 'inputs':
        print(','.join(list(feature_files.keys())))
        return
    if len(sys.argv) == 2 and sys.argv[1] == 'outputs':
        print(','.join(
            [make_header_name(class_name) for (_, class_name) in feature_files.values()]) + ',' +
              feature_list_header_file + ',' + feature_list_source_file)
        return

    name_map = {}

    for src_file, (category_prefix, class_name) in feature_files.items():
        with open(src_file) as fin:
            src = json.loads(fin.read())

        features_json = src['features']
        features = []

        # Go over the list of features and write the header file that declares the features struct
        for feature_json in features_json:
            json_name = feature_json['name']
            var_name = make_camel_case(json_name)
            # Use the same (camelCase) name for display as well
            display_name = var_name
            issue = feature_json.get('issue', None)
            feature = template_feature.format(
                var_name=var_name,
                display_name=display_name,
                category=category_prefix + feature_json['category'],
                description='\n'.join('"' + line + '"' for line in feature_json['description']),
                issue='' if issue is None else '"' + issue + '"')

            features.append(feature)

            # Keep track of the feature names.  Sometimes the same feature name is present in
            # multiple backends.  That's ok for the purposes of feature overriding.
            name_map[var_name] = display_name

        description = '\n'.join(['// ' + line for line in src['description']])
        header_file = make_header_name(class_name)

        header = template_header.format(
            script_name=os.path.basename(__file__),
            input_file_name=src_file,
            description=description.replace(src_file, header_file),
            name=class_name,
            NAME=class_name.upper(),
            features='\n'.join(features))

        with open(header_file, 'w') as fout:
            fout.write(header)
            fout.close()

    # Generate helpers for use by tests to override a feature or not.
    feature_enums = []
    feature_strings = []
    for var_name, display_name in sorted(name_map.items(), key=lambda item: item[0].lower()):
        VarName = var_name[0].upper() + var_name[1:]

        feature_enums.append(template_feature_enum.format(VarName=VarName))

        feature_strings.append(
            template_feature_string.format(VarName=VarName, display_name=display_name))

    with open(feature_list_header_file, 'w') as fout:
        fout.write(
            template_feature_list_header.format(
                script_name=os.path.basename(__file__),
                input_file_name='*_features.json',
                features='\n'.join(feature_enums)))
        fout.close()

    with open(feature_list_source_file, 'w') as fout:
        fout.write(
            template_feature_list_source.format(
                script_name=os.path.basename(__file__),
                input_file_name='*_features.json',
                features='\n'.join(feature_strings)))
        fout.close()


if __name__ == '__main__':
    sys.exit(main())
