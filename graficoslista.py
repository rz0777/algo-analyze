import pandas as pd
import matplotlib.pyplot as plt

# Ler arquivo gerado pelo programa C
df = pd.read_csv("resultados_resumo.csv")

print(df)

# ==========================================
# Gráfico 1 - Tempo Médio x Tamanho do Vetor
# ==========================================

plt.figure(figsize=(10, 6))

for algoritmo in df["Algoritmo"].unique():
    dados = df[df["Algoritmo"] == algoritmo]

    plt.plot(
        dados["Tamanho"],
        dados["Media"],
        marker="o",
        label=algoritmo
    )

plt.title("Tempo Médio de Execução")
plt.xlabel("Tamanho do Vetor")
plt.ylabel("Tempo Médio (s)")
plt.grid(True)
plt.legend()

plt.savefig("grafico_tempo.png")
plt.show()

# ==========================================
# Gráfico 2 - Movimentações
# ==========================================

pivot_mov = df.pivot(
    index="Tamanho",
    columns="Algoritmo",
    values="Movimentacoes"
)

pivot_mov.plot(
    kind="bar",
    figsize=(10, 6)
)

plt.title("Quantidade de Movimentações")
plt.xlabel("Tamanho do Vetor")
plt.ylabel("Movimentações")
plt.grid(axis="y")

plt.tight_layout()
plt.savefig("grafico_movimentacoes.png")
plt.show()

# ==========================================
# Gráfico 3 - Tempo Médio (Escala Log)
# ==========================================

plt.figure(figsize=(10, 6))

for algoritmo in df["Algoritmo"].unique():
    dados = df[df["Algoritmo"] == algoritmo]

    plt.plot(
        dados["Tamanho"],
        dados["Media"],
        marker="o",
        label=algoritmo
    )

plt.xscale("log")
plt.yscale("log")

plt.title("Tempo Médio (Escala Logarítmica)")
plt.xlabel("Tamanho do Vetor")
plt.ylabel("Tempo Médio (s)")
plt.legend()
plt.grid(True)

plt.savefig("grafico_logaritmico.png")
plt.show()

print("\nGráficos gerados:")
print("grafico_tempo.png")
print("grafico_movimentacoes.png")
print("grafico_logaritmico.png")