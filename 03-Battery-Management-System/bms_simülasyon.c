#include <stdio.h>

int main()
{
    // SİMÜLASYON DEĞİŞKENLERİ
    float batarya_sarj = 0.0f;    // %0'dan başlıyor
    float sicaklik = 25.0f;       // Oda sıcaklığından (25 derece) başlıyor
    float hedef_sicaklik = 35.0f; // Bataryayı maksimum 35 derecede sabit tutmak istiyoruz

    // PID DEĞİŞKENLERİ
    float k_p = 1.5f;
    float k_i = 0.1f;
    float k_d = 0.5f;

    float hata = 0.0f;
    float onceki_hata = 0.0f;
    float hata_toplami = 0.0f;
    float hata_degisimi = 0.0f;
    float dt = 0.1f; // Her adım 0.1 saniye

    FILE *dosya = fopen("bms_veri.txt", "w");

    // SİMÜLASYON DÖNGÜSÜ (500 adım sürecek)
    for (int i = 0; i < 500; i++)
    {
        float saniye = i * dt;


        hata = sicaklik - hedef_sicaklik;


        hata_toplami += hata * dt;
        hata_degisimi = (hata - onceki_hata) / dt;


        float kontrol_sinyali = (k_p * hata) + (k_d * hata_degisimi) + (k_i * hata_toplami);

        batarya_sarj += 0.2f; // Pil her adımda %0.2 şarj oluyor

        // Pil şarj olurken ısınır (+0.5 derece), ama bizim ürettiğimiz kontrol_sinyali (fan) onu soğutur
        sicaklik += 0.5f - (kontrol_sinyali * 0.05f);

        // Güvenlik: Sıcaklık oda sıcaklığının (25) altına düşmesin
        if (sicaklik < 25.0f)
            sicaklik = 25.0f;
        if (batarya_sarj > 100.0f)
            batarya_sarj = 100.0f;


        fprintf(dosya, "%.1f %.2f %.2f\n", saniye, batarya_sarj, sicaklik);
        onceki_hata = hata;
    }

    fclose(dosya);
    printf("BMS Simulasyon verisi hazir!\n");
    return 0;
}