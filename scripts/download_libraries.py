import os
import requests
from tqdm import tqdm

urls = [
    "https://sdk.lunarg.com/sdk/download/1.3.261.1/windows/VulkanSDK-1.3.261.1-Installer.exe",
    "https://github.com/microsoft/GDK/archive/refs/tags/June_2023_Update_3.zip",
    "https://storage.googleapis.com/tensorflow/libtensorflow/libtensorflow-gpu-windows-x86_64-2.10.0.zip"
]

download_folder = "downloads"
os.makedirs(download_folder, exist_ok=True)

def download_file_with_progress(url, filepath):
    response = requests.get(url, stream=True)
    if response.status_code == 200:
        full_filepath = os.path.join(download_folder, filepath)
        total_size = int(response.headers.get('content-length', 0))

        progress_bar = tqdm(total=total_size, unit='B', unit_scale=True)

        with open(full_filepath, 'wb') as file:
            for chunk in response.iter_content(chunk_size=8192):
                file.write(chunk)
                progress_bar.update(len(chunk))
        progress_bar.close()
        print(f"Downloaded {full_filepath}")
    else:
        print(f"Failed to download {url}, status code: {response.status_code}")

for url in urls:
    filename = url.split("/")[-1]
    download_file_with_progress(url, filename)
