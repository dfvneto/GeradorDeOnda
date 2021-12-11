// the setup routine runs once when you press reset:
#include <math.h>

// Iteração do loop no tempo
int n = 0;

#define AjustePotenciometro 1023

// Iniiciando leitura dos pinos
void setup()
{
    Serial.begin(9600); // Configuração de saída da porta serial
}

void loop()
{
    float amplitude = analogRead(A5);
    float frequencia = analogRead(A4);
    float fase = analogRead(A3);
    float offSet = analogRead(A2);
    amplitude = (amplitude)*5.00 / AjustePotenciometro;
    offSet = (offSet)*10.00 / AjustePotenciometro;
    fase = (fase)*360.00 / AjustePotenciometro;
    fase = (fase * PI) / 180;
    frequencia = frequencia * 100 / AjustePotenciometro;

    if (frequencia < 1)
        frequencia = 1.;
    frequencia = round(frequencia);
    int N = 30;

    n += 1;
    //  GerarOndaSenoidal(offSet, fase, amplitude, frequencia, N);
    GerarOndaQuadrada(offSet, fase, amplitude, frequencia, N);
    //  GerarOndaTriangular (offSet, fase, amplitude , frequencia, N);
    delay(10);
}

/* DADOS PARA GERAR ONDA SENOIDAL
  sen(Wo*n) -> Função seno. "n" é a iteração.
  Wo = (2*pi)/N -> Frequencia fundamental. "N" é o periodo fundamental.
  Fase = atg(ParteImaginariaNumerador/ParteRealNumerador)
*/
void GerarOndaSenoidal(float offSet, float fase, unsigned long amplitude, float w, int N)
{
    float magnitude = 0;
    float saidaFase = 0;
    float k = 0;
    float Real = 0;
    float Img = 0;
    float w0 = (2 * w * PI) / N;
    for (k = -N / 2; k <= N / 2 - 1; k++)
    {
        if (k == 1)
        {
            Real = Real + (sin(w0 * n)) / 2;
            Img = Img + (cos(w0 * n)) / 2;
        }
        else if (k == -1)
        {
            Real = Real + (sin(w0 * n)) / 2;
            Img = Img - (cos(w0 * n)) / 2;
        }
    }
    if (Img == 0 && Real > 0)
    {
        saidaFase = 0;
    }
    else if (Img == 0 && Real < 0)
    {
        saidaFase = PI;
    }
    else if (Real == 0 && Img > 0)
    {
        saidaFase = PI / 2.;
    }
    else if (Real == 0 && Img < 0)
    {
        saidaFase = -PI / 2.;
    }
    else
    {
        saidaFase = atan(Img / Real);
    }
    magnitude = sqrt(Real * Real + Img * Img);
    magnitude += offSet;
    magnitude *= amplitude;
    //Serial.println(saidaFase);
    //Serial.println(Real);
}

void GerarOndaQuadrada(float offSet, float fase, unsigned long amplitude, float w, int N)
{
    float magnitude = 0;
    float saidaFase = 0;
    float n1 = 5.00;
    float w0 = (2 * w * PI) / N;
    float k = 0;
    float ak = 0;
    float Real = 0;
    float Img = 0;
    for (k = -N / 2; k <= N / 2 - 1; k++)
    {
        if (k == 0)
        {
            ak = (2.00 * n1 + 1.00) / N;
        }
        else
        {
            ak = (1.00 / N) * ((sin(k * w0 * (n1 + 0.5))) / (sin((k * w0) / 2.00)));
        }

        Real = Real + ak * cos(k * n * w0 + fase);
        Img = Img + ak * sin(k * n * w0 + fase);
    }
    if (Img == 0 && Real > 0)
    {
        saidaFase = 0;
    }
    else if (Img == 0 && Real < 0)
    {
        saidaFase = PI;
    }
    else if (Real == 0 && Img > 0)
    {
        saidaFase = PI / 2;
    }
    else if (Real == 0 && Img < 0)
    {
        saidaFase = -PI / 2;
    }
    else
    {
        saidaFase = atan(Img / Real);
    }
    magnitude = sqrt(Real * Real + Img * Img); // calculo do modulo
    magnitude += offSet;
    magnitude *= amplitude;
    //Serial.println(magnitude);
    //Serial.println(saidaFase);
}

void GerarOndaTriangular(float offSet, float fase, unsigned long amplitude, float w, int N)
{
    float magnitude = 0;
    float saidaFase = 0;
    float n1 = 2.00;
    float w0 = (2 * w * PI) / N;
    float k = 0;
    float ak = 0;
    float Real = 0;
    float Img = 0;
    for (k = -N / 2; k <= N / 2 - 1; k++)
    {
        if (k == 0)
        {
            ak = (2.00 * n1 + 1.00) / N;
        }
        else
        {
            ak = (1.00 / N) * ((sin(k * w0 * (n1 + 0.5))) / (sin((k * w0) / 2.00)));
        }
        ak = ak * ak;
        Real = Real + ak * cos(k * n * w0 + fase);
        Img = Img + ak * sin(k * n * w0 + fase);
    }
    if (Img == 0 && Real > 0)
    {
        saidaFase = 0;
    }
    else if (Img == 0 && Real < 0)
    {
        saidaFase = PI;
    }
    else if (Real == 0 && Img > 0)
    {
        saidaFase = PI / 2;
    }
    else if (Real == 0 && Img < 0)
    {
        saidaFase = -PI / 2;
    }
    else
    {
        saidaFase = atan(Img / Real);
    }
    magnitude = sqrt(Real * Real + Img * Img); // calculo do modulo
    magnitude += offSet;
    magnitude *= amplitude;
    //Serial.println(magnitude);
    //Serial.println(saidaFase);
}