# File-Cleaner
Scans files in a local folder, fetches a JSON list of filenames from a remote URL, and deletes files that exist locally but are missing from the remote list.
## Usage
```bash
./image_cleaner -f <folder-path> -u <json-url>
```
### Arguments
| Flag | Description |
|------|-------------|
| `-f` | Local folder to scan for files |
| `-u` | URL returning a JSON array of filenames to keep |
## Example
```bash
./image_cleaner -f "/home/user/pictures" -u "http://example.com/api/filelist"
```
The remote URL should return a JSON array like:
```json
["photo1.jpg", "photo2.png", "image3.webp"]
```
Any file in the local folder not present in this list gets deleted.
## Build
```bash
./build.sh
```


## Extra Repository ##
```
 git remote add codeberg ssh://git@codeberg.org/veto/File-Remover
 git push codeberg -f

```
