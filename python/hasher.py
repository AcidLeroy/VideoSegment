import hashlib
def hashfile(file_name, blocksize=65536):
    hasher = hashlib.sha256()
    with open(file_name, 'rb') as f: 
        buf = f.read(blocksize)
        while len(buf) > 0:
            hasher.update(buf)
            buf = f.read(blocksize)
        return hasher.hexdigest()

