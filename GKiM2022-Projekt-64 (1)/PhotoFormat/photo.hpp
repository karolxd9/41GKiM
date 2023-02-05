#ifndef PHOTO_HPP
#define PHOTO_HPP
#include <exception>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

using namespace std;



class Photo{
private:
    Uint16 height;
    Uint16 width;
    SDL_Window* window;
    SDL_Surface* screen;
    SDL_Color paleta7BW[128];
    SDL_Color paleta7N[128];
    SDL_Color paleta7D[128];
    SDL_Color paleta[(256) * (170)];
    int ileKolorow;

public:

    //konstruktor
    Photo(Uint16 height,Uint16 width,SDL_Window * window,SDL_Surface* screen,int ileKolorow);

    //funckje podstawowe
    void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);
    void setPixelSurface(int x, int y, Uint8 R, Uint8 G, Uint8 B);
    SDL_Color getPixel(int x, int y);
    SDL_Color getPixelSurface(int x, int y, SDL_Surface *surface);
    void ladujBMP(char const* nazwa, int x, int y);
    void czyscEkran(Uint8 R, Uint8 G, Uint8 B);

    //funkcje konwertuj¹ce
    Uint8 z24RGBdo7RGB(SDL_Color kolor);
    SDL_Color z7rgbna24RGB(Uint8 kolor7bit);
    Uint8 z24RGBdo7BW(SDL_Color kolor);
    Uint8 z24RGBdo7BWwithDithering(SDL_Color kolor);
    SDL_Color z7BWdo24RGB(Uint8 BW7bit);


    //funckje wykonuj¹ce konwersje
    void zastosuj24RGBto7RGB();
    void zastosujBW();
    void zastosuj7D();
    void zastosujBWzDitheringiem();
    void zastosuj24RGBto7RGBzDitheringiem();

    //funkcja inicjuj¹ca
    bool init();
    void dodajNaglowek(ofstream & plik,char id[],Uint16 widthImage,Uint16 heightImage,Uint8 mode,bool compression);
    int odczytajNaglowek(ifstream & plik,char id[],Uint16 &widthImage,Uint16 &heightImage,Uint8 &mode,bool &compression);

    bool porownajKolory(SDL_Color kolor1 , SDL_Color kolor2);
    int dodajKolor(SDL_Color kolor);
    int sprawdzKolor(SDL_Color kolor);
    int liczInicjujKolory(SDL_Color paleta[]);
    void stworzDedykowana(SDL_Color paleta7D[]);
    void zbierajKolory();

    //do palety dedykowanej
    void medianCutRGB(int start, int koniec, int iteracja);
    int najwiekszaRoznica(int start, int koniec);
    void sortujKubelekRGB(int start, int koniec, int ktoraSkladowa);
    void narysujObrazekRGB(int px, int py, SDL_Color paleta[]);
    int znajdzSasiadaRGB(SDL_Color kolor, SDL_Color paleta[]);

    //rysowanie palet
    void rysujPaleteBW(SDL_Color paleta7BW []);
    void rysujPaleteN(SDL_Color paleta7N []);
    void rysujPaleteD(SDL_Color paleta7D []);


    //zapis i odczyt obrazu
    void zapisz7RGBbezRLE(bool dithering); //tryb 2
    void zapisz7BWbezRLE(bool dithering); //tryb 3
    void zapisz7DbezRLE(bool dithering);
    void odczyt7RGBbezRLE();
    void odczyt7BWbezRLE();
    void odczyt7DbezRLE();

    //kompresja
    bool czyRGBRLE();
    void RGBRLE();
    void dekompresjaRGBRLE();


    //funkcje dzia³aj¹ce po naciœniêciu odpowiedniego klawisza
    void Funkcja1();
    void Funkcja2();
    void Funkcja3();
    void Funkcja4();
    void Funkcja5();
    void Funkcja6();
    void Funkcja7();
    void Funkcja8();
    void Funkcja9();


};


#endif // PHOTO_HPP

