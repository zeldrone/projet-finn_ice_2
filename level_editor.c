#include<allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<string.h>
#include "header.h"
#include "header_allegro.h"
#include <allegro.h>
#define LIGNE text_height(font)
void triple_buffer(BITMAP* affiche[15][19], int* page)
{

    enable_triple_buffer();
    BITMAP* buffer1;
    BITMAP* buffer2;
    scare_mouse();
    if(*page)
    {
        buffer1= create_bitmap(TSPRITE*19, TSPRITE*15);
        buffer1= affiche_buffer(affiche);
        blit(buffer1, screen,0,0,0,0, 19*TSPRITE, 15*TSPRITE);
        destroy_bitmap(buffer1);
        *page=0;
    }
    else
    {
        buffer2= create_bitmap(TSPRITE*19, TSPRITE*15);
        buffer2= affiche_buffer(affiche);
        blit(buffer2, screen,0,0,0,0, 19*TSPRITE, 15*TSPRITE);
        destroy_bitmap(buffer2);
        *page=1;
    }
    unscare_mouse();
}
int ennemy_editor(BITMAP* affiche[15][19], int tab[15][19], char niveau[50])
{
    int i,j,a=0;
    int nb_ennemi = 0;
    int deplacements_ennemis[50]= {0};
    BITMAP* affiche2[NBSPRITE];
    BITMAP* buffer;
    init_mode_graphique(1, affiche2);
    buffer=create_bitmap(TSPRITE*19,TSPRITE*15);
    buffer=affiche_buffer(affiche);
    FILE* fichier=NULL;

    for (i=0; i<15; i++)
    {
        for(j=0; j<19; j++)
        {
            if (tab[i][j]==66) nb_ennemi++;
        }
    }
    i=0;
    j=0;
    int coord_ennemis[nb_ennemi][2];
    for (i=0; i<15; i++)
    {
        for(j=0; j<19; j++)
        {
            if (tab[i][j]==66)
            {
                coord_ennemis[a][0]=j;
                coord_ennemis[a++][1]=i;
            }
        }
    }
    system("pause");
    for (i=0; i<nb_ennemi; i++)
    {
        for(j=0; j<nb_ennemi; j++)
        {
            affiche[coord_ennemis[j][1]][coord_ennemis[j][0]]=affiche2[7];
        }
        if (strlen(niveau)<40)
        {
            sprintf(niveau, "ennemi.%s.%d", niveau, i);
        }
        else
        {
            allegro_message("le nom est trop long!");
            return 0;
        }
        affiche[coord_ennemis[i][1]][coord_ennemis[i][0]]=affiche2[5];
        a=1;
        deplacements_ennemis[0]=49;
        while(!key[KEY_ENTER])
        {
            if(a<49)
            {
                if(!key[KEY_W])
                {
                    if(!key[KEY_S])
                    {
                        if(!key[KEY_A])
                        {
                            if(!key[KEY_D])
                            {
                                if(key[KEY_X]) return 0;
                            }
                            else
                            {
                                coord_ennemis[i][0]++;
                                deplacements_ennemis[a++]=1;
                            }
                        }
                        else
                        {
                            coord_ennemis[i][0]--;
                            deplacements_ennemis[a++]=2;
                        }
                    }
                    else
                    {
                        coord_ennemis[i][1]++;
                        deplacements_ennemis[a++]=3;
                    }
                }
                else
                {
                    coord_ennemis[i][1]--;
                    deplacements_ennemis[a++]=4;
                }

            draw_sprite(buffer, affiche2[5], TSPRITE*coord_ennemis[i][0], TSPRITE*coord_ennemis[i][1]);
            blit(buffer, screen, 0,0,0,0, TSPRITE*19, TSPRITE*15);
        }
        }
        if(menu_oui_non(buffer, "mouvement"))
        {
            for(a=0; a<50; a++)
            {
                deplacements_ennemis[a]=0;
                i--;
            }
            allegro_message("Le mouvement a été annulé\nEntrez le mouvement de cet ennemi");
        }
        else
        {
            for(a=0; a<50; a++)
            {
                fprintf(fichier, "%d ", deplacements_ennemis[a]);
            }
            allegro_message("mouvement enregistré!");
        }
    }
return 0;
}
int sauvegarde_niveau(int valeurs[15][19], char mot[50])
{
    int nb,i=0,j=0;
    FILE* noms_sauvegardes;
    FILE* sauvegarde;
    noms_sauvegardes= fopen("noms_sauvegardes.txt", "r+t");
    fscanf(noms_sauvegardes, "%d", &nb);
    if (strlen(mot)<44)
    {
        strcat(mot, ".txt");
    }
    else
    {
        allegro_message("le nom est trop long!");
        return 1;
    }
    sauvegarde = fopen(mot, "w+");

    fseek(noms_sauvegardes, 0, SEEK_SET);
    fprintf(noms_sauvegardes, "%d ", ++nb);
    fseek(noms_sauvegardes, 0, SEEK_END);
    fprintf(noms_sauvegardes, " %s", mot);
    i=0;
    j=0;
    for (i=0; i<15; i++)
    {
        for(j=0; j<19; j++)
        {
            fprintf(sauvegarde, "%d ", valeurs[i][j]);
        }
    }
    fclose(sauvegarde);
    fclose(noms_sauvegardes);
    return 0;
}
int conversion(int num, int *compteur)
{
    switch (num)
    {
    case 0:
        num= 2;
        break;
    case 1:
        num= -2;
        break;
    case 2:
        num= -50;
        break;

    case 3:
        num= 100;
        break;
    case 4:
        num= 1;
        break;
    case 5:
        num= 66;
        break;
    case 6:
        num= -1;
        break;
    case 7:
        num= 0;
        break;
    case 8:
        num= 3;
        break;
    case 9:
        num= 5;
        break;
    case 10:
        num=4;
        break;
    case 11:
        num= 7;
        break;
    case 12:
        num=8;
        break;
    case 13:
        num=101+((*compteur)%2)*10+(*compteur)-(*compteur)%2;
        (*compteur)++;
        break;
    default:
        num=-2;
    }
    return num;
}

int menu_oui_non(BITMAP* buffer, char* mot)
{
    BITMAP* sauvegarde;
    BITMAP* ecran_noir;
    int compteur=0;
    ecran_noir= create_bitmap(192+5*32, 160);
    clear_to_color(ecran_noir, makecol(0, 0, 0));
    sauvegarde= create_bitmap(19*TSPRITE, 15*TSPRITE);
    textprintf_ex(ecran_noir, font, 0, 0, makecol(255, 255, 255),-1, "voulez-vous sauvegarder ce %s?", mot);
    blit(ecran_noir, sauvegarde,0,0,0,0, 19*TSPRITE, 15*TSPRITE);
    textprintf_ex(ecran_noir, font, 0, LIGNE+7, makecol(255, 255, 255),-1, "-> oui        non");
    draw_sprite(buffer, ecran_noir, 192-2*32, 160);
    blit(buffer, screen,0,0,0,0, 19*TSPRITE, 15*TSPRITE);
    rest(200);
    while(!key[KEY_ENTER])
    {
        if((key[KEY_LEFT])||(key[KEY_A]))
        {
            blit(sauvegarde, ecran_noir,0,0,0,0, 19*TSPRITE, 15*TSPRITE);
            textprintf_ex(ecran_noir, font, 0, LIGNE+7, makecol(255, 255, 255),-1, "-> oui        non");
            draw_sprite(buffer, ecran_noir, 192-2*32, 160);
            blit(buffer, screen,0,0,0,0, 19*TSPRITE, 15*TSPRITE);
            compteur=0;
        }
        if((key[KEY_RIGHT]||key[KEY_D]))
        {
            blit(sauvegarde, ecran_noir,0,0,0,0, 19*TSPRITE, 15*TSPRITE);
            textprintf_ex(ecran_noir, font, 0, LIGNE+7, makecol(255, 255, 255),-1, "   oui     -> non");
            draw_sprite(buffer, ecran_noir, 192-2*32, 160);
            blit(buffer, screen,0,0,0,0, 19*TSPRITE, 15*TSPRITE);
            compteur=1;
        }

    }
    clear_keybuf();
    return compteur;
}

void editeur_de_case(BITMAP* affiche[15][19], int valeurs[15][19])
{
    int compteur=0;
    int Case=0;
    int test=1,x=100,y=100;
    int page=0;
    BITMAP* affiche2[NBSPRITE];
    init_mode_graphique(1, affiche2);
    show_mouse(screen);
    rest(500);
    while (test)
    {


        poll_mouse();
        triple_buffer(affiche, &page);
        scare_mouse();
        if ((mouse_b & 1))
        {
            if (((int)(mouse_x-mouse_x%TSPRITE)/TSPRITE!=x)||((int)(mouse_y-mouse_y%TSPRITE)/TSPRITE!=y))
            {
                Case=0;
                x = (int)(mouse_x-mouse_x%TSPRITE)/TSPRITE;
                y =(int)(mouse_y-mouse_y%TSPRITE)/TSPRITE;
                affiche[(int)(mouse_y-mouse_y%TSPRITE)/TSPRITE][(int)(mouse_x-mouse_x%TSPRITE)/TSPRITE] = affiche2[Case];
                valeurs[(int)(mouse_y-mouse_y%TSPRITE)/TSPRITE][(int)(mouse_x-mouse_x%TSPRITE)/TSPRITE] = conversion(Case, &compteur);
                triple_buffer(affiche, &page);
                rest(100);
            }
            else
            {
                if (Case==13)
                {
                    Case=-1;
                    compteur--;
                }
                affiche[(int)(mouse_y-mouse_y%TSPRITE)/TSPRITE][(int)(mouse_x-mouse_x%TSPRITE)/TSPRITE]=affiche2[++Case];
                valeurs[(int)(mouse_y-mouse_y%TSPRITE)/TSPRITE][(int)(mouse_x-mouse_x%TSPRITE)/TSPRITE]= conversion(Case, &compteur);
                triple_buffer(affiche, &page);
                rest(100);

            }

        }
        if (key[KEY_ENTER])
        {
            if (compteur%2==1)
            {
                allegro_message("attention!\n les telporteurs sont liées 2 à 2! il ne peut pas y en avoir un nombre impair!");
            }
            else test--;
        }

        if(mouse_b & 2)
        {
            if (Case==9) compteur--;
            Case=7;
            x= (int)(mouse_x-mouse_x%TSPRITE)/TSPRITE;
            y=(int)(mouse_y-mouse_y%TSPRITE)/TSPRITE;
            affiche[(int)(mouse_y-mouse_y%TSPRITE)/TSPRITE][(int)(mouse_x-mouse_x%TSPRITE)/TSPRITE]=affiche2[Case];
            valeurs[(int)(mouse_y-mouse_y%TSPRITE)/TSPRITE][(int)(mouse_x-mouse_x%TSPRITE)/TSPRITE]= conversion(Case, &compteur);
            triple_buffer(affiche, &page);
            rest(100);
        }
    }
}
void worst_writing_ever(char mot[50], BITMAP* buffer, BITMAP* ecran_noir, int line, BITMAP* affiche[15][19])
{
    int a=0;
    int key_allegro;
    char key_ascii;
    int i=0;
    draw_sprite(buffer, ecran_noir, 192-2*32, 160);
    blit(buffer, screen,0,0,0,0, 19*TSPRITE, 15*TSPRITE);
    rest(200);
    while(!key[KEY_ENTER])
    {
        key_allegro=readkey();
        key_ascii= key_allegro & 0xff;

        if((key_ascii >= 32) && (key_ascii <= 126))
        {
            if (i<49)
            {
                mot[i]= key_ascii;
                for(a=0; a<i+1; a++)textprintf_ex(ecran_noir, font, a*text_length(font, "O"), line*LIGNE+5, makecol(255, 255, 255),-1, "%c", mot[a]);
                a=0;
                destroy_bitmap(buffer);
                buffer=affiche_buffer(affiche);
                draw_sprite(buffer, ecran_noir, 192-2*32, 160);
                blit(buffer, screen,0,0,0,0, 19*TSPRITE, 15*TSPRITE);
                mot[i+1]='\0';
                i++;
            }
        }
    }

    mot[i]='\0';
}

BITMAP* affiche_buffer(BITMAP* affiche[15][19])
{
    BITMAP* buffer;
    buffer= create_bitmap(TSPRITE*19, TSPRITE*15);
    int i,j;

    for (i=0; i<15; i++)
    {
        for(j=0; j<19; j++)
        {
            if (affiche[i][j]!=NULL) draw_sprite(buffer, affiche[i][j], TSPRITE*j, TSPRITE*i);
        }
    }

    return buffer;
}
void level_editor()
{
    int i,j;
    BITMAP* buffer;
    BITMAP* ecran_noir;
    char mot[50];
    mot[0]='c';
    mot[1]='\0';
    install_mouse();
    enable_hardware_cursor();
    install_timer();
    BITMAP* affiche[15][19]= {{load_bitmap("mur.bmp", NULL)}};
    ecran_noir= create_bitmap(192+5*32, 160);
    clear_to_color(ecran_noir, makecol(0, 0, 0));
    buffer= create_bitmap(TSPRITE*19, TSPRITE*15);
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED, TSPRITE*19, TSPRITE*15, 0, 0)==0)
    {
        affiche[0][0]=load_bitmap("mur.bmp", NULL);
        for (i=0; i<15; i++)
        {
            for(j=0; j<19; j++)
            {
                affiche[i][j]=affiche[0][0];
                if (affiche[i][j]!=NULL) draw_sprite(buffer, affiche[i][j], TSPRITE*j, TSPRITE*i);
            }
        }
        textprintf_ex(ecran_noir, font, 0, LIGNE, makecol(255,255,255),-1, "bienvenue sur l'editeur de niveau");
        draw_sprite(buffer, ecran_noir, 192-2*32, 160);
        blit(buffer, screen,0,0,0,0, 19*TSPRITE, 15*TSPRITE);
        rest(1100);
        menu(buffer, affiche, mot);
        destroy_bitmap(buffer);
    }
}
void menu(BITMAP* buffer, BITMAP* affiche[15][19], char mot[50])
{
    int x=1,i,j;
    BITMAP* ecran_noir;
    BITMAP* sauvegarde[15][19];
    BITMAP* ecran_selec;
    int valeurs[15][19];
    int line;
    ecran_noir= create_bitmap(192+5*32, 160);
    ecran_selec= create_bitmap(192+5*32, 160);
    clear_to_color(ecran_noir, makecol(0, 0, 0));
    textprintf_ex(ecran_noir, font, 0, LIGNE, makecol(255,255,255),-1, "Que souhaitez-vous faire?");
    textprintf_ex(ecran_noir, font, 0, 2*LIGNE+3, makecol(255,255,255),-1, "'dessin' pour commencer a dessiner");
    textprintf_ex(ecran_noir, font, 0, 3*LIGNE+3, makecol(255,255,255),-1, "'aide' pour voir l'aide au dessin!important!");
    blit(ecran_noir, ecran_selec, 0,0,0,0, 192+5*32, 160 );
    line=4;
    affiche[0][0]=load_bitmap("mur.bmp", NULL);
    for (i=0; i<15; i++)
    {
        for(j=0; j<19; j++)
        {
            valeurs[i][j]=-2;
            printf("%d",valeurs[i][j]);
            affiche[i][j]=affiche[0][0];
            if (affiche[i][j]!=NULL) draw_sprite(buffer, affiche[i][j], TSPRITE*j, TSPRITE*i);
        }
        printf("\n");
    }
    draw_sprite(buffer, ecran_noir, 192-2*32, 160);
    blit(buffer, screen,0,0,0,0, 21*TSPRITE, 15*TSPRITE);
    while(x)
    {
        i=0;
        j=0;
        for (i=0; i<15; i++)
        {
            for(j=0; j<19; j++)
            {

                sauvegarde[i][j]=affiche[i][j];
            }
        }
        worst_writing_ever(mot, buffer, ecran_noir, line, affiche);
        if (strcmp(mot, "dessin"))
        {
            if (strcmp(mot, "aide"))
            {
                allegro_message("ce n'est pas une entree valable");
            }
            else
            {
                clear_to_color(ecran_noir, makecol(0,0,0));
                textprintf_ex(ecran_noir, font, 0, LIGNE+3, makecol(255,255,255),-1, "Afin de dessiner un niveau cliquez sur les cases.");
                textprintf_ex(ecran_noir, font, 0, 2*(LIGNE+3), makecol(255,255,255),-1, "un clic gauche fais afficher la possibilité suivante");
                textprintf_ex(ecran_noir, font, 0, 3*(LIGNE+3), makecol(255,255,255),-1, "un clic droit met une glace a l'emplacement indiqué");
                textprintf_ex(ecran_noir, font, 0, 4*(LIGNE+3), makecol(255,255,255),-1, "appuyez sur entree quand vous avez terminé");
                textprintf_ex(ecran_noir, font, 0, 5*(LIGNE+3), makecol(255,255,255),-1, "Ce jeu n'est pas multijoueur! poser deux joueurs se soldera par un echec dans l'execution du niveau");
                textprintf_ex(ecran_noir, font, 0, 6*(LIGNE+3), makecol(255,255,255),-1, "Les teleporteurs vont pas paires et sont liés dans l'ordre dans le quel vous les implémentez!");
                textprintf_ex(ecran_noir, font, 0, 7*(LIGNE+3), makecol(255,255,255),-1, "une seule sortie ou tunnel!! Le tunnel eclipsera la sortie le cas échéant mais plusieurs d'entre eux conduiront a un échec");
                textprintf_ex(ecran_noir, font, 0, 8*(LIGNE+3), makecol(255,255,255),-1, "Soyez créatifs!!!");
            }
        }
        else
        {
            editeur_de_case(affiche, valeurs);
            ennemy_editor(affiche, valeurs, mot);
            buffer=affiche_buffer(affiche);
            draw_sprite(buffer, ecran_noir, 192-2*32, 160);
            blit(buffer, screen,0,0,0,0, 21*TSPRITE, 15*TSPRITE);
            x=menu_oui_non(buffer, "dessin");
            line++;
            if(x==0)
            {
                clear_to_color(ecran_noir, makecol(0,0,0));
                textprintf_ex(ecran_noir, font, 0, 0, makecol(255,255,255),-1, "entrez le nom de votre niveau");
                worst_writing_ever(mot, buffer, ecran_noir, 1, affiche);
                if (sauvegarde_niveau(valeurs, mot));
                else
                {
                    allegro_message("niveau enregistre!");
                    x=0;
                }
            }
            else
            {

                for (i=0; i<15; i++)
                {
                    for(j=0; j<19; j++)
                    {
                        affiche[i][j]=sauvegarde[i][j];
                    }
                }
            }
        }
        blit(ecran_selec, ecran_noir, 0,0,0,0, 192+5*32, 160 );
    }
}

