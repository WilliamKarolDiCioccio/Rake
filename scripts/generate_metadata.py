import os
from datetime import datetime
import pytz
from tzlocal import get_localzone

def generate_metadata_header(project_name, project_version):
    local_now = datetime.now()

    local_tz = get_localzone()

    local_build_date = local_now.strftime("%Y-%m-%d")
    local_build_time = local_now.strftime("%H:%M:%S")

    gmt_central_now = local_now.astimezone(pytz.utc)

    gmt_build_date = gmt_central_now.strftime("%Y-%m-%d")
    gmt_build_time = gmt_central_now.strftime("%H:%M:%S")

    additional_info = f"// Metadata generated in local timezone: {local_tz}\n// Good work fellow programmer!\n"

    metadata_header = f"""#pragma once

#define PROJECT_NAME "{project_name}"
#define PROJECT_VERSION "{project_version}"
#define LOCAL_BUILD_DATE "{local_build_date}"
#define LOCAL_BUILD_TIME "{local_build_time}"
#define GMT_BUILD_DATE "{gmt_build_date}"
#define GMT_BUILD_TIME "{gmt_build_time}"

{additional_info}"""

    return metadata_header

def write_metadata_header(metadata_header, output_file):
    with open(output_file, 'w') as f:
        f.write(metadata_header)

if __name__ == "__main__":
    project_name = "RakeEngine"
    project_version = "0.0"

    # Output file path considering the project root directory
    output_file = "./include/metadata.hpp"

    metadata_header = generate_metadata_header(project_name, project_version)

    write_metadata_header(metadata_header, output_file)

    print(f"Metadata header file '{output_file}' generated successfully.")
