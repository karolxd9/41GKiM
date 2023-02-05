#include "photo.hpp"

// konstruktor funkcji Photo
Photo::Photo(Uint16 height,Uint16 width,SDL_Window * window,SDL_Surface* screen,int ileKolorow){
    this->height=height;
    this->width=width;
    this->window=NULL;
    this->screen=NULL;
    this->ileKolorow=ileKolorow;
}

//ustawianie koloru dnaego Pixela
void Photo::setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
  if ((x>=0) && (x<width) && (y>=0) && (y<height))
  {
    /* Zamieniamy poszczególne składowe koloru na format koloru piksela */
    Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

    /* Pobieramy informację ile bajtów zajmuje jeden piksel */
    int bpp = screen->format->BytesPerPixel;

    /* Obliczamy adres piksela */
    Uint8 *p1 = (Uint8 *)screen->pixels + (y*2) * screen->pitch + (x*2) * bpp;
    Uint8 *p2 = (Uint8 *)screen->pixels + (y*2+1) * screen->pitch + (x*2) * bpp;
    Uint8 *p3 = (Uint8 *)screen->pixels + (y*2) * screen->pitch + (x*2+1) * bpp;
    Uint8 *p4 = (Uint8 *)screen->pixels + (y*2+1) * screen->pitch + (x*2+1) * bpp;

    /* Ustawiamy wartość piksela, w zależnoœci od formatu powierzchni*/
    switch(bpp)
    {
        case 1: //8-bit
            *p1 = pixel;
            *p2 = pixel;
            *p3 = pixel;
            *p4 = pixel;
            break;

        case 2: //16-bit
            *(Uint16 *)p1 = pixel;
            *(Uint16 *)p2 = pixel;
            *(Uint16 *)p3 = pixel;
            *(Uint16 *)p4 = pixel;
            break;

        case 3: //24-bit
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p1[0] = (pixel >> 16) & 0xff;
                p1[1] = (pixel >> 8) & 0xff;
                p1[2] = pixel & 0xff;
                p2[0] = (pixel >> 16) & 0xff;
                p2[1] = (pixel >> 8) & 0xff;
                p2[2] = pixel & 0xff;
                p3[0] = (pixel >> 16) & 0xff;
                p3[1] = (pixel >> 8) & 0xff;
                p3[2] = pixel & 0xff;
                p4[0] = (pixel >> 16) & 0xff;
                p4[1] = (pixel >> 8) & 0xff;
                p4[2] = pixel & 0xff;
            } else {
                p1[0] = pixel & 0xff;
                p1[1] = (pixel >> 8) & 0xff;
                p1[2] = (pixel >> 16) & 0xff;
                p2[0] = pixel & 0xff;
                p2[1] = (pixel >> 8) & 0xff;
                p2[2] = (pixel >> 16) & 0xff;
                p3[0] = pixel & 0xff;
                p3[1] = (pixel >> 8) & 0xff;
                p3[2] = (pixel >> 16) & 0xff;
                p4[0] = pixel & 0xff;
                p4[1] = (pixel >> 8) & 0xff;
                p4[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4: //32-bit
            *(Uint32 *)p1 = pixel;
            *(Uint32 *)p2 = pixel;
            *(Uint32 *)p3 = pixel;
            *(Uint32 *)p4 = pixel;
            break;

        }
    }
}

void Photo::setPixelSurface(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
  if ((x>=0) && (x<width*2) && (y>=0) && (y<height*2))
  {
    /* Zamieniamy poszczególne składowe koloru na format koloru piksela */
    Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

    /* Pobieramy informację ile bajtów zajmuje jeden piksel */
    int bpp = screen->format->BytesPerPixel;

    /* Obliczamy adres piksela */
    Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;

    /* Ustawiamy wartość piksela, w zależności od formatu powierzchni*/
    switch(bpp)
    {
        case 1: //8-bit
            *p = pixel;
            break;

        case 2: //16-bit
            *(Uint16 *)p = pixel;
            break;

        case 3: //24-bit
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            } else {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4: //32-bit
            *(Uint32 *)p = pixel;
            break;
        }
    }
}

SDL_Color Photo::getPixel(int x, int y) {
    SDL_Color color ;
    Uint32 col = 0 ;
    if ((x>=0) && (x<width) && (y>=0) && (y<height)) {
        //określamy pozycję
        char* pPosition=(char*)screen->pixels ;

        //przesunięcie względem y
        pPosition+=(screen->pitch*y*2) ;

        //przesunięcie względem x
        pPosition+=(screen->format->BytesPerPixel*x*2);

        //kopiujemy dane piksela
        memcpy(&col, pPosition, screen->format->BytesPerPixel);

        //konwertujemy kolor
        SDL_GetRGB(col, screen->format, &color.r, &color.g, &color.b);
    }
    return ( color ) ;
}

SDL_Color Photo::getPixelSurface(int x, int y, SDL_Surface *surface) {
    SDL_Color color ;
    Uint32 col = 0 ;
    if ((x>=0) && (x<width) && (y>=0) && (y<height)) {
        //określamy pozycję
        char* pPosition=(char*)surface->pixels ;

        //przesunięcie względem y
        pPosition+=(surface->pitch*y) ;

        //przesunięcie względem x
        pPosition+=(surface->format->BytesPerPixel*x);

        //kopiujemy dane piksela
        memcpy(&col, pPosition, surface->format->BytesPerPixel);

        SDL_GetRGB(col, surface->format, &color.r, &color.g, &color.b);
    }
    return ( color ) ;
}

//funckja do załączenia obrazu BMP do konwersji
void Photo::ladujBMP(char const* nazwa, int x, int y)
{
    SDL_Surface* bmp = SDL_LoadBMP(nazwa);
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
    }
    else
    {
        SDL_Color kolor;
        for (int yy=0; yy<bmp->h; yy++) {
			for (int xx=0; xx<bmp->w; xx++) {
				kolor = getPixelSurface(xx, yy, bmp);
				setPixel(xx, yy, kolor.r, kolor.g, kolor.b);
			}
        }
		SDL_FreeSurface(bmp);
        SDL_UpdateWindowSurface(window);
    }

}

//czyszczenie ekranu
void Photo::czyscEkran(Uint8 R, Uint8 G, Uint8 B)
{
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, R, G, B));
    SDL_UpdateWindowSurface(window);
}

//konwersja z 24-bitów RGB do 7 bitów RGB
Uint8 Photo::z24RGBdo7RGB(SDL_Color kolor){
    int R,G,B;
    int r,g,b;
    Uint8 kolor7bit;

    R=kolor.r;
    G=kolor.g;
    B=kolor.b;

    r=R>>6;
    g=G>>5;
    b=B>>6;

    kolor7bit=(r<<5)+(g<<2)+(b);

    return kolor7bit;
}

// powrót z 7 bitowej wersji RGB do 24 bitowej wartości
SDL_Color Photo::z7rgbna24RGB(Uint8 kolor7bit){
    SDL_Color kolor;
    kolor.r=(kolor7bit & 0b01100000)<<1;
    kolor.g=(kolor7bit & 0b00011100)<<3;
    kolor.b=(kolor7bit & 0b00000011)<<6;

    return kolor;
}

//zamiana z 24 bitowej wersji RGB na 7 bitową skalę szarości
Uint8 Photo::z24RGBdo7BW(SDL_Color kolor){
    Uint8 R,G,B;

    R=kolor.r;
    G=kolor.g;
    B=kolor.b;


    Uint8 bw=(R*0.299+G*0.587+B*0.114);
    bw=(bw >> 1);
    return bw;

}

//funkcja do zastosowania dla całego obrazu(zamiana z 24 RGB do 7 RGB)
void Photo::zastosuj24RGBto7RGB(){
    for(int j=0;j<height/2;j++){
        for(int i=0;i<width/2;i++){
            SDL_Color kolor;
            int kolor2;
            SDL_Color kolor3;
            kolor=getPixel(i,j);


            int R,G,B,nowyR,nowyG,nowyB;
            R=kolor.r;
            G=kolor.g;
            B=kolor.b;
            //cout<<(int)(R)<<" "<<(int)(G)<<" "<<(int)(B)<<"\n";
            //kolor2=z24RGBdo7RGB(kolor);
            //cout<<(int)(kolor2)<<endl;
            //kolor3=z7rgbna24RGB(kolor2);
            //cout<<(int)(kolor3.r)<<" "<<(int)(kolor3.g)<<" "<<(int)(kolor3.b)<<"\n";
            nowyR=R>>3;
            nowyG=G>>3;
            nowyB=B>>2;

            R=nowyR<<3;
            G=nowyG<<3;
            B=nowyB<<2;
            setPixel(i+width/2,j,R,G,B);
        }
    }

}

//funkcja do zastosowania dla całego obrazu(zamiana z 24 RGB do 7 BW)
void Photo::zastosujBW(){
    for(int j=0;j<height/2;j++){
        for(int i=0;i<width/2;i++){
            SDL_Color kolor;
            kolor=getPixel(i,j);
            Uint8 R,G,B;
            R=kolor.r;
            G=kolor.g;
            B=kolor.b;
            Uint8 kolor2=z24RGBdo7BW(kolor);
            setPixel(i+width/2,j,kolor2,kolor2,kolor2);


            SDL_Color kolor3;
            kolor3=z7BWdo24RGB(kolor2);
            setPixel(i,j+height/2,kolor3.r,kolor3.g,kolor3.b);

        }
    }
}

//funkcja do zastosowania dla całego obrazu(zamiana z 24 RGB do 7 RGB z ditheringiem)
void Photo::zastosujBWzDitheringiem(){
    SDL_Color kolor,nowyKolor,noweBW;
    Uint8 BW, kwantyzacja,orginalna;

    float bledy[(width/2)+2][(height/2)+1];
    memset(bledy,0,sizeof(bledy));

    float blad=0;
    int przesuniecie=1;

    for(int j=0;j<height/2;j++){
        for(int i=0;i<width/2;i++){
            kolor=getPixel(i,j);
            orginalna=0.299*kolor.r+0.587*kolor.g+0.114*kolor.b;
            orginalna+=bledy[i+przesuniecie][j];

            if(orginalna > 255) orginalna=255;
            if(orginalna < 0) orginalna=0;

            kwantyzacja = z24RGBdo7BW({orginalna,orginalna,orginalna});
            kwantyzacja = z7BWdo24RGB(kwantyzacja).r;

            blad = orginalna - kwantyzacja;

            bledy[i+przesuniecie + 1][j] += blad*7.0/16.0;
			bledy[i+przesuniecie + 1][j+1] +=blad*1.0/16.0;
			bledy[i+przesuniecie][j+1] +=blad*5.0/16.0;
			bledy[i+przesuniecie-1][j+1] +=blad*3.0/16.0;

            noweBW = {orginalna, orginalna, orginalna};
            BW = z24RGBdo7BW(noweBW);
            nowyKolor = z7BWdo24RGB(BW);

            setPixel(i+width/2, j , nowyKolor.r , nowyKolor.g , nowyKolor.b);
        }
    }



}

//zamiana z 7 bitowej skali szarości na 24 bitową wersję RGB
SDL_Color Photo::z7BWdo24RGB(Uint8 BW7bit){
    int R,G,B;
    SDL_Color kolor;
    kolor.r=(BW7bit<<1);
    kolor.g=(BW7bit<<1);
    kolor.b=(BW7bit<<1);

    return kolor;
};

//porównuje czy dwa kolory są identyczne
bool Photo::porownajKolory(SDL_Color kolor1 , SDL_Color kolor2)
{
    if(kolor1.r != kolor2.r)
        return false;
    if(kolor1.g != kolor2.g)
        return false;
    if(kolor1.b != kolor2.b)
        return false;

    return true;
}

//dodaje kolor do palety
int Photo::dodajKolor(SDL_Color kolor)
{
    int aktualnyKolor = this->ileKolorow;
    paleta[aktualnyKolor] = kolor;
    // cout<<aktualnyKolor<<": ["<<(int)kolor.r<<", "<<(int)kolor.g<<", "<<(int)kolor.b<<"]"<<endl;
    this->ileKolorow++;
    return aktualnyKolor;
}

//sprawdza czy kolor już występuje w palecie
int Photo::sprawdzKolor(SDL_Color kolor)
{
    if(ileKolorow>0)
    {
        for(int k =0; k<ileKolorow; k++)
        {
            if(porownajKolory(kolor,paleta[k]))
            {
               return k;
            }
        }
    }
    return dodajKolor(kolor);
}

//inicjacja odpowiedniej palety, zwraca liczbę różnych kolorów na obrazie
int Photo::liczInicjujKolory(){
    ileKolorow = 0;
    SDL_Color kolor;
    int nrKoloru = 0;

    for(int j = 0; j<width/2; j++)
    {
        for(int i = 0; i<height/2;i++)
        {
            kolor = getPixel(i,j);
            nrKoloru = sprawdzKolor(kolor);
        }
    }

    if (ileKolorow < 128) {
        for(int k =0; k<128; k++) {
            paleta7D[k] = {0,0,0};
        }
        for (int k=0; k<ileKolorow; k++) {
            paleta7D[k] = paleta[k];
        }
    }

    for (int k=0; k<128; k++) {
            paleta7N[k] = z7rgbna24RGB(k);
            paleta7BW[k] = z7BWdo24RGB(k);
    }

    return this->ileKolorow;
}

//rysuje kolory palety odcieni szarości
void Photo::rysujPaleteBW(SDL_Color paleta7BW []){

    for(int i=0;i<128;i++){
        for(int j=width/2;j<width;j++){
            setPixel(j,i,paleta7BW[i].r,paleta7BW[i].g,paleta7BW[i].b);
        }
    }
}

//rysuje kolory palety narzuconej
void Photo::rysujPaleteN(SDL_Color paleta7N []){
    for(int i=170;i<340;i++){
        for(int j=0;j<width/2;j++){
            setPixel(j,i,paleta7N[(340-i)].r,paleta7N[(340-i)].g,paleta7N[(340-i)].b);
        }
    }
}

//dodaje dane do nagłówka
void Photo::dodajNaglowek(ofstream & plik,char id[],Uint16 widthImage,Uint16 heightImage,Uint8 mode,bool compression){
    plik.open("nowy.bin",ios::binary);
    plik.write((char*)(&id),sizeof(char)*3);
    plik.write((char*)(&widthImage),sizeof(Uint16));
    plik.write((char*)(&heightImage),sizeof(Uint16));
    plik.write((char*)(&mode),sizeof(Uint8));
    plik.write((char*)(&compression),sizeof(bool));
}

int Photo::odczytajNaglowek(ifstream & plik,char id[],Uint16 &widthImage,Uint16 &heightImage,Uint8 &mode,bool &compression){


    plik.read((char*)(&id),sizeof(char)*3);
    plik.read((char*)(&widthImage),sizeof(Uint16));
    plik.read((char*)(&heightImage),sizeof(Uint16));
    plik.read((char*)(&mode),sizeof(Uint8));
    plik.read((char*)(&compression),sizeof(bool));

    cout << "Odczyt obrazka ID: " << id << "\n";
    cout << "Tryb: " <<         (int)mode << "\n";
    cout << "Szerokosc: " <<    (int)heightImage << "\n";
    cout << "Wysokosc: " <<     (int)widthImage << "\n";
    cout << "kompresja: " <<    (bool)compression << "\n\n";

    return (int)(mode);
}

void Photo::zapisz7RGBbezRLE(bool dithering){
    ofstream plik;
    char id[]="MPS";
    int R,G,B,r=0,g=0,b=0;
    SDL_Color kolor,nowyKolor;
    int wartosc[(width/2)*(height/2)]{};
    int licznik=0;
    dodajNaglowek(plik,id,256,170,2,0);
    float bledyr[(width/2)+2][(height/2)+1];
    float bledyg[(width/2)+2][(height/2)+1];
    float bledyb[(width/2)+2][(height/2)+1];

    memset(bledyr,0,sizeof(bledyr));
    memset(bledyg,0,sizeof(bledyg));
    memset(bledyb,0,sizeof(bledyb));

    float bladr=0;
    float bladg=0;
    float bladb=0;
    int przesuniecier=1;
    int przesuniecieg=1;
    int przesuniecieb=1;

    for(int j=0;j<height/2;j++){
        for(int i=0;i<width/2;i++){
            kolor=getPixel(i,j);

            if(dithering){
                R=kolor.r;
                G=kolor.g;
                B=kolor.b;

                R+=bledyr[i+przesuniecier][j];
                G+=bledyg[i+przesuniecieg][j];
                B+=bledyb[i+przesuniecieb][j];

                if (R > 255) {
                    R = 255;
                }
                else if ( R < 0 ) {
                    R = 0;
                }

                if (G > 255) {
                    G = 255;
                }
                else if ( G < 0 ) {
                    G = 0;
                }

                if (B > 255) {
                    B = 255;
                }
                else if ( B < 0 ) {
                    B = 0;
                }

                bladr = R - z7rgbna24RGB(z24RGBdo7RGB({R,G,B})).r;
                bladg = G - z7rgbna24RGB(z24RGBdo7RGB({R,G,B})).g;
                bladb = B - z7rgbna24RGB(z24RGBdo7RGB({R,G,B})).b;

                nowyKolor.r=R;
                nowyKolor.g=G;
                nowyKolor.b=B;

                bledyr[i+przesuniecier+1][j]+=bladr*7.0/16.0;
                bledyr[i+przesuniecier+1][j+1]+=bladr*1.0/16.0;
                bledyr[i+przesuniecier][j+1]+=bladr*5.0/16.0;
                bledyr[i+przesuniecier-1][j+1]+=bladr*3.0/16.0;

                bledyg[i+przesuniecieg+1][j]+=bladg*7.0/16.0;
                bledyg[i+przesuniecieg+1][j+1]+=bladg*1.0/16.0;
                bledyg[i+przesuniecieg][j+1]+=bladg*5.0/16.0;
                bledyg[i+przesuniecieg-1][j+1]+=bladg*3.0/16.0;

                bledyb[i+przesuniecieb+1][j]+=bladb*7.0/16.0;
                bledyb[i+przesuniecieb+1][j+1]+=bladb*1.0/16.0;
                bledyb[i+przesuniecieb][j+1]+=bladb*5.0/16.0;
                bledyb[i+przesuniecieb-1][j+1]+=bladb*3.0/16.0;

                wartosc[licznik]=z24RGBdo7RGB(nowyKolor);
                plik.write((char*)(&wartosc[licznik]),sizeof(int));
                licznik++;

            }
            else{
                 wartosc[licznik]=(int)(z24RGBdo7RGB(kolor));
                 plik.write((char*)(&wartosc[licznik]),sizeof(int));
                 licznik++;
            }
        }
    }
    plik.close();
    cout<<"Plik nowy.bin został zapisany 7 RGB"<<endl;
}

void Photo::odczyt7RGBbezRLE(){
    int licznik=0;
    SDL_Color kolor2;
    Uint8 wartosc[(width/2)*(height/2)];
    ifstream plik;
    plik.open("nowy.bin",ios::binary);
    char id[3];
    Uint16 widthImage,heightImage;
    Uint8 mode;
    bool compression;
    odczytajNaglowek(plik,id,widthImage,heightImage,mode,compression);
    for(int j=0;j<height/2;j++){
        for(int i=0;i<width/2;i++){
            plik.read((char*)(&wartosc[licznik]), sizeof(int));
            kolor2=z7rgbna24RGB(wartosc[licznik]);
            licznik++;
            setPixel(i,j+height/2,kolor2.r,kolor2.g,kolor2.b);
            //cout<<(int)(kolor2.r)<<" "<<(int)(kolor2.g)<<" "<<(int)(kolor2.b)<<"\n";
        }
    }
    plik.close();


}

void Photo::zapisz7BWbezRLE(bool dithering){
    ofstream plik("nowy7BW.bin",ios::binary);
    char id[]="MPS";
    dodajNaglowek(plik,id,width/2,height/2,3,0);
    float bledy[(width/2)+2][(height/2)+1];
    memset(bledy,0,sizeof(bledy));
    float blad=0;
    int przesuniecie=1;
    SDL_Color kolor;
    int BW[(width/2)*(height/2)]{},bw;
    int licznik=0;
    for(int j=0;j<height/2;j++){
        for(int i=0;i<width/2;i++){
            kolor=getPixel(i,j);

            if(dithering){
                bw=z24RGBdo7BW(kolor);
                bw+=(int)(bledy[i+przesuniecie][j]);
                if(bw>255){
                    bw=255;
                }
                else if(bw<0){
                    bw=0;
                }
                blad=bw-z24RGBdo7BW(kolor);
                bledy[i+przesuniecie+1][j]+=blad*7.0/16.0;
                bledy[i+przesuniecie+1][j+1]+=blad*1.0/16.0;
                bledy[i+przesuniecie][j+1]+=blad*5.0/16.0;
                bledy[i+przesuniecie-1][j+1]+=blad*3.0/16.0;

            }
            else{
                BW[licznik]=z24RGBdo7BW(kolor);
                plik.write((char*)(&BW[licznik]),sizeof(int));
                licznik++;
            }
            przesuniecie++;
        }
    }
    plik.close();
}



//zamiana z 24 bitowej wersji kolorowej do 7 bitowej
void Photo::Funkcja1() {
    zapisz7RGBbezRLE(true);
    odczyt7RGBbezRLE();
    SDL_UpdateWindowSurface(window);
}
//zamiana z 24 RGB na 7 BW
void Photo::Funkcja2() {
    zapisz7BWbezRLE(false);

    SDL_UpdateWindowSurface(window);
}

//zamiana na obraz z kolorów palety dedykowanej
void Photo::Funkcja3() {
    cout<<liczInicjujKolory()<<endl;
    rysujPaleteBW(paleta7BW);
}

void Photo::Funkcja4() {

    SDL_UpdateWindowSurface(window);
}

//rysuj palete
void Photo::Funkcja5() {

    SDL_UpdateWindowSurface(window);
}

void Photo::Funkcja6() {

    //...

    SDL_UpdateWindowSurface(window);
}

void Photo::Funkcja7() {

    //...

    SDL_UpdateWindowSurface(window);
}

void Photo::Funkcja8() {

    //...

    SDL_UpdateWindowSurface(window);
}

void Photo::Funkcja9() {

    //...

    SDL_UpdateWindowSurface(window);
}

//funkcja inicjująca
bool Photo::init(){
    const char *tytul="Grupa 41 Przybycin Mordarski Sobon";
    Uint16 szerokosc=this->width;
    Uint16 wysokosc=this->height;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
    }

    window = SDL_CreateWindow(tytul, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szerokosc*2, wysokosc*2, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    screen = SDL_GetWindowSurface(window);
    if (screen == NULL) {
        fprintf(stderr, "SDL_GetWindowSurface Error: %s\n", SDL_GetError());
    return false;
    }
    SDL_UpdateWindowSurface(window);


    bool done = false;
    SDL_Event event;
    // główna pętla programu
    while (SDL_WaitEvent(&event)) {
        // sprawdzamy czy pojawiło się zdarzenie
        switch (event.type) {
            case SDL_QUIT:
                done = true;
                break;

            // sprawdzamy czy został wciśnięty klawisz
            case SDL_KEYDOWN: {
                // wychodzimy, gdy wciśnięto ESC
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    done = true;
                if (event.key.keysym.sym == SDLK_1)
                    Funkcja1();
                if (event.key.keysym.sym == SDLK_2)
                    Funkcja2();
                if (event.key.keysym.sym == SDLK_3)
                    Funkcja3();
                if (event.key.keysym.sym == SDLK_4)
                    Funkcja4();
                if (event.key.keysym.sym == SDLK_5)
                    Funkcja5();
                if (event.key.keysym.sym == SDLK_6)
                    Funkcja6();
                if (event.key.keysym.sym == SDLK_7)
                    Funkcja7();
                if (event.key.keysym.sym == SDLK_8)
                    Funkcja8();
                if (event.key.keysym.sym == SDLK_9)
                    Funkcja9();
                if (event.key.keysym.sym == SDLK_a)
                    ladujBMP("obrazek1.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_s)
                    ladujBMP("obrazek2.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_d)
                    ladujBMP("obrazek3.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_f)
                    ladujBMP("obrazek4.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_g)
                    ladujBMP("obrazek5.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_h)
                    ladujBMP("obrazek6.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_j)
                    ladujBMP("obrazek7.bmp", 0, 0);
                if (event.key.keysym.sym == SDLK_b)
                    czyscEkran(0, 0, 10);
                else
                    break;
               }
        }
        if (done) break;
    }

    if (screen) {
        SDL_FreeSurface(screen);
    }

    if (window) {
        SDL_DestroyWindow(window);
    }


    SDL_Quit();
}


