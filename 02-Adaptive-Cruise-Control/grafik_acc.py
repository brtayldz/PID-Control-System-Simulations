import matplotlib.pyplot as plt

saniyeler, ondeki_hizlar, bizim_hizlar, mesafeler = [], [], [], []

try:
    with open("acc_veri.txt", "r") as dosya:
        for satir in dosya:
            saniye, o_hiz, b_hiz, mesafe = satir.split()
            saniyeler.append(float(saniye))
            ondeki_hizlar.append(float(o_hiz))
            bizim_hizlar.append(float(b_hiz))
            mesafeler.append(float(mesafe))
except FileNotFoundError:
    print("Hata: 'acc_veri.txt' bulunamadı kanka!")
    exit()

# İki grafik üst üste çizeceğiz (Subplot)
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 8), sharex=True)

# 1. Grafik: HIZLAR
ax1.plot(saniyeler, ondeki_hizlar, label="Öndeki Aracın Hızı (km/h)", color="orange", linestyle="--", linewidth=2)
ax1.plot(saniyeler, bizim_hizlar, label="Bizim Aracın Hızı (ACC) (km/h)", color="blue", linewidth=2)
ax1.set_ylabel("Hız (km/h)", fontsize=11)
ax1.title.set_text("Adaptive Cruise Control (ACC) Hız ve Mesafe Simülasyonu")
ax1.grid(True, linestyle=":", alpha=0.6)
ax1.legend(loc="upper right")

# 2. Grafik: TAKİP MESAFESİ
ax2.plot(saniyeler, mesafeler, label="Anlık Mesafe (Metre)", color="red", linewidth=2)
ax2.axhline(y=20, color="green", linestyle=":", label="Güvenli Hedef Mesafe (20m)")
ax2.set_xlabel("Zaman (Saniye)", fontsize=11)
ax2.set_ylabel("Mesafe (Metre)", fontsize=11)
ax2.grid(True, linestyle=":", alpha=0.6)
ax2.legend(loc="upper right")

plt.tight_layout()
plt.show()