import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv(
    "Evol_Pop.txt", sep=" ", header=None, names=["Iteration", "Proies", "Predateurs"]
)

print(data)


it = data["Iteration"]

plt.plot(it, data["Proies"], c="green", linewidth=1)
plt.plot(it, data["Predateurs"], c="red", linewidth=1)

plt.legend(["proies", "prédateurs"], loc="upper right")

plt.show()
