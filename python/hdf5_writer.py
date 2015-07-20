import numpy as np
import h5py as h5
from hasher import hashfile
from extractor import Extractor
from read_video import VideoHelper
import matplotlib.pyplot as plt

def WriteFromPkl(hdf5_file, movie_file):
    """
    After calling annotate, this function takes the pickled file and transforms it 
    to hdf5. This function actually reads the video chunks that specified in the 
    pickled file and writes that region.
    """
    base = movie_file.split(".")[0]
    pkl_file = ''.join([base, ".pkl"])
    ex = Extractor(pkl_file)

    with h5.File(hdf5_file, 'a') as f:
        grp = f.create_group("typing/{}".format(movie_file.split("/")[-1]))
        grp.attrs['movie_file'] = movie_file.split("/")[-1]
        grp.attrs['sha1'] = hashfile(movie_file)[:16]

        vh = VideoHelper(movie_file)
        print("Total frames is: {}".format(vh.total_frames))

        # frame range
        prev_frange = None
        for fidx, frange in enumerate(ex.GetFrames()): 
            if not(prev_frange == frange):
                print("Extractor frame range is: {} at index: {}".format(frange, fidx))
                fgrp = grp.create_group("frames{}-{}".format(frange[0], frange[1]))
                f_buffer = vh.ReadFrameRange(frange[0], frange[1])
                # cube range
                for cidx, cube in enumerate(ex.GetCubeArrays(fidx)):
                   indices = ex.GetNpIndices(cube) 
                   new_idx = (np.index_exp[:]) + (indices)
                   aoi = f_buffer[new_idx]
                   #aoi = aoi[indices]
                   dset = fgrp.create_dataset("image_cube{}".format(cidx), data=aoi)
                   dset.attrs['top_left_x'] = cube[0][0]
                   dset.attrs['top_left_y'] = cube[0][1]
                   dset.attrs['width'] = cube[1]
                   dset.attrs['height'] = cube[2]
                   print("cube is: {}".format(cube))
            prev_frange = frange
