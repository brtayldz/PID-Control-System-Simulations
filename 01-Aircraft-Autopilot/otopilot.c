#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#define BEKLE(ms) Sleep(ms)
#else
#include <unistd.h>
#define BEKLE(ms) usleep(ms * 1000)
#endif

#define KP 0.5f
#define KI 0.15f
#define KD 0.8f

int main()
{
    float mevcut_yukseklik = 0.0f;
    float hedef_yukseklik = 50.0f;
    float hiz = 0.0f;
    float yercekimi = -9.81f;
    float motor_itki = 0.0f;

    float hata = 0.0f;
    float onceki_hata = 0.0f;
    float hata_toplami = 0.0f;
    float hata_degisimi = 0.0f;

    float dt = 0.1f;

    FILE *dosya = fopen("simulasyon_veri.txt", "w");
    if (dosya == NULL)
    {
        printf("Hata: Dosya olusturulamadi!\n");
        return 1;
    }

    printf("=== OTOPILOT SIMULASYONU BASLIYOR ===\n");
    printf("Veriler 'simulasyon_veri.txt' dosyasina yaziliyor...\n");

    for (int i = 0; i < 400; i++)
    {

        hata = hedef_yukseklik - mevcut_yukseklik;
        hata_toplami += hata * dt;
        hata_degisimi = (hata - onceki_hata) / dt;

        motor_itki = (KP * hata) + (KI * hata_toplami) + (KD * hata_degisimi);

        if (motor_itki < 0)
            motor_itki = 0;
        if (motor_itki > 20)
            motor_itki = 20;

        float ivme = motor_itki + yercekimi;
        hiz += ivme * dt;
        mevcut_yukseklik += hiz * dt;

        if (mevcut_yukseklik < 0)
        {
            mevcut_yukseklik = 0;
            hiz = 0;
        }

        float saniye = i * dt;

        fprintf(dosya, "%.1f %.2f\n", saniye, mevcut_yukseklik);

        onceki_hata = hata;
        BEKLE(10);
    }

    fclose(dosya);
    printf("Simulasyon bitti! Veriler hazir.\n");
    return 0;
}