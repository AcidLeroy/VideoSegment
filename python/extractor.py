import unittest
import pickle
import numpy as np

class Extractor: 
    def __init__(self, filename): 
        suffix = filename.split(".")[1] 
        if (suffix != "pkl"): 
            raise RuntimeError("Must use a pkl file")
        self.data = pickle.load(open(filename, "rb"))

    def GetFrames(self): 
        "Get a list of all the frame ranges that have valid data."
        frames = []; 
        for frame in self.data: 
            frames.append((frame[0], frame[1])); 
        return frames; 

    def GetCubeArrays(self, pos): 
        "Get a cube array for a frame range position"
        cubes = []
        for cube in self.data[pos][2]: 
            cubes.append(cube)
        return cubes

    def GetNpIndices(self, cube): 
        """
        Given a cube (rectangle over range of frames), return the indices 
        necessary to index into the full frame. 
        """

        #cube = cube[0]
        tx = cube[0][0]; 
        ty = cube[0][1]; 
        width = cube[1]; 
        bx = tx + width; 
        height = cube[2]; 
        by = ty + height

        if (bx < tx): 
            # swap 
            tx, bx = bx, tx
        if (by < ty): 
            # swap
            ty, by = by, ty

        # Index into array with [row, col]
        return (np.index_exp[ty:(by + 1), tx:(bx + 1), :])


class ExtractorTestCase(unittest.TestCase):
    def setUp(self):
        self.three_cubes_file = "three_cubes.pkl"
        self.ex = Extractor(self.three_cubes_file); 

    def test_RaisesError(self): 
      with self.assertRaises(RuntimeError):
        Extractor("test.mp3")

    def test_GetFrames(self):
        frames = self.ex.GetFrames()
        self.assertEqual(3, len(frames)) 

    def test_GetFramesValues(self):
        frames = self.ex.GetFrames()
        # Check that the first frame range is what I expect
        self.assertEqual(0, frames[0][0]); 
        self.assertEqual(9, frames[0][1]); 
    
    def test_GetCubeArraysSize(self): 
        cubes = self.ex.GetCubeArrays(0); 
        self.assertEqual(1, len(cubes))

    def test_GetNpIndices(self): 
        cube = [(138.0, 100.0), 287.0, 126.0]
        truth = np.index_exp[100.0:(100.0+126.0+1), 138.0:(138.0+287.0+1), :]
        actual = self.ex.GetNpIndices(cube); 
        self.assertEqual(truth, actual)

if __name__ == '__main__':
    unittest.main()
