import numpy as np

f=open('emily.data','w')

l_data=1000 # 1000 examples
l_x=12 # 12 inputs
l_y=8 # 8 outputs
dim=(l_x+l_y,l_data)

xy=np.ndarray(dim)
r=np.arange(l_data)

th=0 # phase (rad)
for i in range(dim[0]):
    if i<l_x:
        xy[i,:]=np.cos(r+th)
    else:
        xy[i,:]=np.sinh(r+th)
    th+=0.13

for i in range(dim[1]):
    f.write(
        '{0},{1},{2},{3},{4},{5},{6},{7},{8},{9},{10},{11},{12},{13},{14},{15},{16},{17},{18},{19}\n'.format(
        xy[0,i],xy[1,i],xy[2,i],xy[3,i],xy[4,i],xy[5,i],xy[6,i],
        xy[7,i],xy[8,i],xy[9,i],xy[10,i],xy[11,i],xy[12,i],xy[13,i],
        xy[14,i],xy[15,i],xy[16,i],xy[17,i],xy[18,i],xy[19,i]))
