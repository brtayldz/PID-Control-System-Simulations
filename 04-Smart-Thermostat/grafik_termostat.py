import matplotlib.pyplot as plt

saniyeler, oda_sicakliklari = [], []

with open("termostat_veri.txt", "r") as dosya:
    for satir in dosya:
        saniye, sicaklik = satir.split()
        saniyeler.append(float(saniye))
        oda_sicakliklari.append(float(sicaklik))

plt.figure(figsize=(10, 5))
plt.plot(saniyeler, oda_sicakliklari, label="Oda Sıcaklığı (°C)", color="darkorange", linewidth=2.5)
plt.axhline(y=22, color="blue", linestyle="--", label="Hedef Sıcaklık (22°C)")
plt.axhline(y=-5, color="cyan", linestyle=":", label="Dış Hava Sıcaklığı (-5°C)")

plt.title("Akıllı Termostat PID Oda Sıcaklığı Kontrolü", fontsize=14, fontweight='bold')
plt.xlabel("Zaman (Saniye)", fontsize=12)
plt.ylabel("Sıcaklık (°C)", fontsize=12)
plt.grid(True, linestyle=":", alpha=0.6)
plt.legend(loc="lower right")

plt.show()