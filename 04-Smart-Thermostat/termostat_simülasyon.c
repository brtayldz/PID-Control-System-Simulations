#include <stdio.h>

int main() {
    // SİMÜLASYON DEĞİŞKENLERİ
    float oda_sicakligi = 10.0f;    // Ev başta buz gibi, 10 derece
    float hedef_sicaklik = 22.0f;   // Kombiyi 22 dereceye ayarlıyoruz
    float dis_sicaklik = -5.0f;     // Dışarısı dondurucu soğuk
    
    // PID DEĞİŞKENLERİ
    float k_p = 2.0f;
    float k_i = 0.2f;
    float k_d = 1.0f;
    
    float hata = 0.0f;
    float onceki_hata = 0.0f;
    float hata_toplami = 0.0f;
    float hata_degisimi = 0.0f;
    float dt = 0.1f; 

    FILE *dosya = fopen("termostat_veri.txt", "w");
    if (dosya == NULL) {
        printf("Hata: Dosya acilamadi!\n");
        return 1;
    }
    
    // 600 adımlık simülasyon
    for (int i = 0; i < 600; i++) {
        float saniye = i * dt;

        hata = hedef_sicaklik - oda_sicakligi; 
        
        hata_toplami += hata * dt; 
        hata_degisimi = (hata - onceki_hata) / dt;

        float kontrol_sinyali = (k_p * hata) + (k_d * hata_degisimi) + (k_i * hata_toplami);

        float isi_kaybi = (oda_sicakligi - dis_sicaklik) * 0.02f;
        float kombi_isisi = kontrol_sinyali * 0.1f;
        
        if (kombi_isisi < 0.0f) kombi_isisi = 0.0f;

        oda_sicakligi += kombi_isisi - isi_kaybi;

        fprintf(dosya, "%.1f %.2f\n", saniye, oda_sicakligi);
        onceki_hata = hata;
    }

    fclose(dosya);
    printf("Termostat simülasyon verisi hazir!\n");
    return 0;
}