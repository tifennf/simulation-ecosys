#! /usr/bin/python3

# 21135979
# FABRICI Tifenn
# Intensif

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

data = pd.read_csv(
    "./data/Eco_Stats.txt",
    sep=" ",
    header=None,
    names=["Iteration", "Proies", "Predateurs"],
)

print("\n")
print("Population final moyenne:")
print("- Proies:", np.mean(data["Proies"]))
print("- Prédateurs:", np.mean(data["Predateurs"]))

print("Nombre d'itération moyen:", np.mean(data["Iteration"]))
