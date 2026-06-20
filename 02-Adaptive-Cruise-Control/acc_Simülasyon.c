#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
    #define BEKLE(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define BEKLE(ms) usleep(ms * 1000)
#endif

// ACC için tatlı PID katsayıları
#define KP 0.8f
#define KI 0.05f
#define KD 0.4f

int main() {
    // Bizim aracın durumları
    float bizim_hiz = 90.0f;          // Saatte 90 km ile başlıyoruz
    float hedef_mesafe = 20.0f;       // Öndeki araçla hep 20 metre mesafe korumak istiyoruz
    float bizim_konum = 0.0f;

    // Öndeki hayali aracın durumları
    float ondeki_hiz = 90.0f;
    float ondeki_konum = 20.0f;       // Aramızda tam 20 metre var (Tam hedefteyiz)

    // PID Değişkenleri
    float hata = 0.0f;
    float onceki_hata = 0.0f;
    float hata_toplami = 0.0f;
    float hata_degisimi = 0.0f;
    
    float dt = 0.1f; // 100 ms örnekleme zamanı

    // Verileri yazacağımız yeni dosya
    FILE *dosya = fopen("acc_veri.txt", "w");
    if (dosya == NULL) {
        printf("Hata: Dosya olusturulamadi!\n");
        return 1;
    }

    printf("=== ACC (AKILLI SEYIR KONTROLU) SIMULASYONU BASLIYOR ===\n");
    printf("Veriler 'acc_veri.txt' dosyasina yaziliyor...\n");

    // 30 saniyelik bir sürüş simülasyonu yapıyoruz (300 döngü)
    for (int i = 0; i < 300; i++) {
        float saniye = i * dt;

        // SENARYO: 5. saniyede öndeki araç aniden frene basıp hızını 50 km/h'e düşürüyor!
        if (saniye >= 5.0f && saniye < 15.0f) {
            ondeki_hiz = 50.0f;
        }
        // SENARYO DEVAMI: 15. saniyede öndeki araç tekrar gaza basıp 100 km/h'e çıkıyor
        else if (saniye >= 15.0f) {
            ondeki_hiz = 100.0f;
        }

        // Araçların konumlarını güncelle (km/h -> m/s çevrimi için 3.6'ya bölüyoruz)
        ondeki_konum += (ondeki_hiz / 3.6f) * dt;
        bizim_konum += (bizim_hiz / 3.6f) * dt;

        // Mevcut mesafe ve Hata hesabı
        float mevcut_mesafe = ondeki_konum - bizim_konum;
        
        // Dikkat kanka: Hedef mesafeden ne kadar uzaktayız?
        // Eğer mesafe azaldıysa hata negatif olur, PID fren kararı verir.
        hata = mevcut_mesafe - hedef_mesafe; 
        
        hata_toplami += hata * dt;
        hata_degisimi = (hata - onceki_hata) / dt;

        // PID pedal çıktısı (Pozitifse GAZ, Negatifse FREN)
        float pedal_kontrol = (KP * hata) + (KI * hata_toplami) + (KD * hata_degisimi);

        // Aracın hızını pedal kontrolüne göre güncelle
        bizim_hiz += pedal_kontrol * dt;

        // Güvenlik sınırları (Araba geri vitese takmasın veya uçmasın)
        if (bizim_hiz < 0.0f) bizim_hiz = 0.0f;
        if (bizim_hiz > 140.0f) bizim_hiz = 140.0f;

        // Dosyaya yaz: Saniye, Öndeki Hız, Bizim Hız, Mevcut Mesafe
        fprintf(dosya, "%.1f %.2f %.2f %.2f\n", saniye, ondeki_hiz, bizim_hiz, mevcut_mesafe);

        onceki_hata = hata;
        BEKLE(5);
    }

    fclose(dosya);
    printf("ACC Simulasyonu bitti! Veriler kaydoldu.\n");
    return 0;
}