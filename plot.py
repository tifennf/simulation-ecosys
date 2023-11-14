#! /usr/bin/python3

# 21135979
# FABRICI Tifenn
# Intensif

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

pop = pd.read_csv(
    "./data/Evol_Pop.txt",
    sep=" ",
    header=None,
    names=["Iteration", "Proies", "Predateurs"],
)

print("\n")
print("Population moyenne:")
print("- Proies:", np.mean(pop["Proies"]))
print("- Prédateurs:", np.mean(pop["Predateurs"]))

it = pop["Iteration"]

plt.plot(it, pop["Proies"], c="green", linewidth=1)
plt.plot(it, pop["Predateurs"], c="red", linewidth=1)

plt.legend(["proies", "prédateurs"], loc="upper right")

plt.show()
