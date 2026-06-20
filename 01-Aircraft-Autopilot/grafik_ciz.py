import matplotlib.pyplot as plt

saniyeler = []
yukseklikler = []

# C kodunun ürettiği dosyayı okuyoruz
try:
    with open("simulasyon_veri.txt", "r") as dosya:
        for satir in dosya:
            saniye, yukseklik = satir.split()
            saniyeler.append(float(saniye))
            yukseklikler.append(float(yukseklik))
except FileNotFoundError:
    print("Hata: 'simulasyon_veri.txt' bulunamadı! Önce C kodunu çalıştır kanka.")
    exit()

# Grafiği janti bir mühendislik raporu moduna sokuyoruz
plt.figure(figsize=(10, 5))
plt.plot(saniyeler, yukseklikler, label="Uçağın Yüksekliği", color="red", linewidth=2)
plt.axhline(y=50, color="blue", linestyle="--", label="Hedef (50m)") # Hedef çizgisi

# Grafik süslemeleri
plt.title("PID Otopilot Yükseklik Simülasyonu", fontsize=14, fontweight='bold')
plt.xlabel("Zaman (Saniye)", fontsize=12)
plt.ylabel("Yükseklik (Metre)", fontsize=12)
plt.grid(True, linestyle=":", alpha=0.6)
plt.legend(loc="lower right")

# Grafiği ekrana basıyoruz
plt.show()