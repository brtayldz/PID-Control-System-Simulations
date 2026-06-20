import matplotlib.pyplot as plt

saniyeler, sarjlar, sicakliklar = [], [], []

with open("bms_veri.txt", "r") as dosya:
    for satir in dosya:
        saniye, sarj, sicak = satir.split()
        saniyeler.append(float(saniye))
        sarjlar.append(float(sarj))
        sicakliklar.append(float(sicak))

fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 8), sharex=True)

# 1. Grafik: Şarj Yüzdesi
ax1.plot(saniyeler, sarjlar, label="Batarya Şarj Yüzdesi (%)", color="green", linewidth=2)
ax1.set_ylabel("Şarj (%)", fontsize=11)
ax1.title.set_text("Gömülü BMS - Batarya Şarj ve Sıcaklık PID Kontrolü")
ax1.grid(True, linestyle=":", alpha=0.6)
ax1.legend(loc="lower right")

# 2. Grafik: Sıcaklık Kontrolü
ax2.plot(saniyeler, sicakliklar, label="Anlık Batarya Sıcaklığı (°C)", color="red", linewidth=2)
ax2.axhline(y=35, color="blue", linestyle="--", label="Hedef Güvenli Sıcaklık (35°C)")
ax2.set_xlabel("Zaman (Saniye)", fontsize=11)
ax2.set_ylabel("Sıcaklık (°C)", fontsize=11)
ax2.grid(True, linestyle=":", alpha=0.6)
ax2.legend(loc="upper right")

plt.tight_layout()
plt.show()