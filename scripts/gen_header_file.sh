#!/bin/bash

root_dir=$1  
output_file="my_struct_in_c.h"
former_output_file = ${root_dir}+"/"+${output_file}

traverse_directory() {
    local dir="$1"

    find "$dir" -maxdepth 1 -type f -name "*.h" | while read -r file; do
        rel_path="${file#$root_dir/}"
        echo "#include \"$rel_path\"" >> "$output_file"
    done

    find "$dir" -maxdepth 1 -mindepth 1 -type d | while read -r subdir; do
        traverse_directory "$subdir"
    done
}


rm -f ${former_output_file}

echo "#ifndef __MY_STRUCT_IN_C_H__" > "$output_file"
echo "#define __MY_STRUCT_IN_C_H__" >> "$output_file"
echo "" >> "$output_file"

traverse_directory "$root_dir"

echo "" >> "$output_file"
echo "#endif /* __MY_STRUCT_IN_C_H__ */" >> "$output_file"

cp ${output_file} ${root_dir}