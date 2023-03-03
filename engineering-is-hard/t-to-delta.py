#!/usr/bin/env/python
import typing

# Get user input
R1 = float(input("Enter R1: "))
R2 = float(input("Enter R2: "))
R3 = float(input("Enter R3: "))

# Calculate RA - RC
numerator = (R1*R2 + R2*R3 + R1*R3)
RA = numerator/R1
RB = numerator/R2
RC = numerator/R3

# Print Wye Circuit
print('''
     R1      R2                   R1 = {R1} Ω
 X ──⋙  ──┬──⋙  ── Y              R2 = {R2} Ω
          │                       R3 = {R3} Ω
          ≶  R3
          │
          Z
'''.format(R1=R1, R2=R2, R3=R3))

# Print Delta Circuit
print ('''
          RC                      RA = {RA} Ω
x ────────⋙  ─────── y            RB = {RB} Ω
 ⋱                 ⋰              RC = {RC} Ω
   ⋱             ⋰
 RB  ⋙        ⋙   RA
      ⋱     ⋰
        ⋱ ⋰
'''.format(RA=RA, RB=RB, RC=RC))
