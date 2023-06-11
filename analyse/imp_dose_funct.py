### Function for analysis output data ###

## Import library ##
# Module with scientific computing functions (matrix/vector)
import numpy as np
# Modules with reading MHD/raw format
import SimpleITK as sitk
# Modules with reading/writing folder/file functions
import os

## Set the filenames and read data from mhd/raw file (Dose Gate) ## 
def SetFile(output_folder, input_dose, input_squared, input_uncert):         
    f_dose = os.path.join(output_folder, input_dose)
    f_squared = os.path.join(output_folder, input_squared)   
    f_uncert = os.path.join(output_folder, input_uncert)  
    # Dose
    dose_gate = sitk.ReadImage(f_dose)
    dose = sitk.GetArrayFromImage(dose_gate)
    # Squared Dose
    squared_gate = sitk.ReadImage(f_squared)
    squared = sitk.GetArrayFromImage(squared_gate)
    # Uncertainty dose
    uncert_gate= sitk.ReadImage(f_uncert)
    uncert = sitk.GetArrayFromImage(uncert_gate)
    # Image rotations 
    dose = np.swapaxes(dose,0,2)
    dose = np.flip(dose,2)
    squared = np.swapaxes(squared,0,2)
    squared = np.flip(squared,2)
    uncert = np.swapaxes(uncert,0,2)
    uncert = np.flip(uncert,2)
    return dose, squared, uncert

## Dose/Uncertainty Evaluation: Percentage Depth Dose (PDD) ##
def dose_z(dose, squared):
    dz = 0.0
    dz_array = []
    # Variance of dose
    squared_dz = 0.0
    # The relative uncertainty of dose 
    delta_dz = 0.0 
    delta_dz_array = []
    for z in range (0,11): # range ( 0, total voxel)
        for y in range(4,7): # range ( (total voxel/2)-1.5, (total voxel/2)-1.5 +3) )
            for x in range (4,7): # range ( (total voxel/2)-1.5, (total voxel/2)-1.5 +3) )
                dz = dz + dose[x,y,z]
                squared_dz = squared_dz + squared[x,y,z]
                if dz != 0:
                    delta_dz = ((np.sqrt(squared_dz))/dz)*100
                else:
                    delta_dz = 0
        dz_array.append(dz)
        delta_dz_array.append(delta_dz)
        dz = 0.0
        squared_dz = 0.0
        delta_dz = 0.0      
    return dz_array, delta_dz_array

## Dose/Uncertainty Evaluation: Off Center Ratio (OCR) ##
def dose_y(dose, squared, z_depth):
    dy = 0.0
    dy_array = []
    # Variance of dose
    squared_dy = 0.0
    # The relative uncertainty of dose 
    delta_dy = 0.0 
    delta_dy_array = []
    for y in range (0,11): # range ( 0, total voxel)
        for x in range(4,7): # range ( (total voxel/2)-1.5, (total voxel/2)-1.5 +3) )
            for z in range (z_depth,z_depth+1):
                dy = dy + dose[x,y,z]
                squared_dy = squared_dy + squared[x,y,z]
                if dy != 0:
                    delta_dy = ((np.sqrt(squared_dy))/dy)*100
                else:
                    delta_dy = 0
        dy_array.append(dy)
        delta_dy_array.append(delta_dy)
        dy = 0.0
        squared_dy = 0.0
        delta_dy = 0.0      
    return dy_array, delta_dy_array

