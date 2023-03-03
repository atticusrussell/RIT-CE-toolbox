import math

print('Sums two phasors')
print('Enter r and theta of V1')
v1_r = float(input('Enter r: '))
v1_theta = float(input('Enter theta: '))

print('Enter r and theta of V2')
v2_r = float(input('Enter r: '))
v2_theta = float(input('Enter theta: '))

v1_x = v1_r * math.cos(math.radians(v1_theta))
v1_y = v1_r * math.sin(math.radians(v1_theta))

v2_x = v2_r * math.cos(math.radians(v2_theta))
v2_y = v2_r * math.sin(math.radians(v2_theta))

Z_x = v1_x + v2_x
Z_y = v1_y + v2_y

print("Z={}+j({})".format(Z_x, Z_y))

Z_r = math.sqrt(math.pow(Z_x,2)+math.pow(Z_y,2))
Z_theta = math.atan(Z_y/Z_x)

print("Z={}∠{}".format(Z_r,math.degrees(Z_theta)))