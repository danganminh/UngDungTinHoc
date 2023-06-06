### Dose/Uncertainty Evaluation: Percentage Depth Dose (PDD) and Off Center Ratio (OCR) ###
### Date: 20/02/2022 ###

#############################
####### Import library ######
#############################

from imp_dose_funct import *
from pathlib import Path
import os
import numpy as np

#############################
###### Read output data #####
#############################

# Change by your own output folder 
output_folder = Path('./output')

# Read mhd/raw file: dose, dose squared  and dose uncertainty 
dose, squared, uncert = SetFile(output_folder, 'run01-Dose.mhd', 'run01-Dose-Squared.mhd', 'run01-Dose-Uncertainty.mhd')

#############################
#### PDD + uncertainties ####
#############################
dz, delta_dz = dose_z(dose, squared)

# Data folder after analysis
os.makedirs('./output/data_analysis', exist_ok=True)
dir_path = Path ('./output/data_analysis')

# Depth values: stat=5, stop=485, num=97
depth = np.linspace(10,110,11)

# Save dose_z file: in txt
name_dz = 'dose_z.txt'
folder_dz = os.path.join(dir_path, name_dz)
header_dz = 'z(mm) dose_z(Gy) delta_dose_z'
dz_col = np.column_stack([depth, dz, delta_dz])
fmt_col = ['%i','%.2e','%.2f']
np.savetxt(folder_dz, dz_col, fmt=fmt_col, header=header_dz)
print('Save file', name_dz)

#############################
#### OCR + uncertainties ####
#############################
z_depth = 10 # Voxel number of depth; "5" mean 30 mm
dy, delta_dy = dose_y(dose, squared, z_depth)

# Position values: stat=-240, stop=240, num=97
position = np.linspace(-55,55,11)

# Save dose_y file: in txt
name_dy = 'dose_y.txt'
folder_dy = os.path.join(dir_path, name_dy)
header_dy = 'y(mm) dose_y(Gy) delta_dose_y'
dy_col = np.column_stack([position, dy, delta_dy])
fmt_col = ['%i','%.2e','%.2f']
np.savetxt(folder_dy, dy_col, fmt=fmt_col, header=header_dy)
print('Save file', name_dy)

# test visual --------------------------------------------------------------------------
print(type(dz))
print("len of depth", len(depth))
