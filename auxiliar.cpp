//---------------------------------------------------------------------------

#include <vcl.h>
#include <fstream>
#include <io.h>

#pragma hdrstop

#include "auxiliar.h"
#include <StrUtils.hpp>
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------

map<int,AnsiString> indexes;
//---------------------------------------------------------------------------

void CrearMenuOrdenar(ListaMenuOrdenar lista, AnsiString defecto,
                      TTable *tabla, TMenuItem *MenuItemOrdenar,
                      void __fastcall (__closure *funcion)(TObject *))
{
        ListaMenuOrdenar::iterator iter;
        TMenuItem *menuitem;
        static int c = 0;

        for (iter = lista.begin(); iter != lista.end(); iter++)
        {
                menuitem = new TMenuItem(MenuItemOrdenar);
                menuitem->Caption = (*iter).second;
                menuitem->RadioItem = true;
                menuitem->Tag = c;
                menuitem->OnClick = funcion;
                MenuItemOrdenar->Add(menuitem);
                if ((*iter).first == defecto)
                {
                        menuitem->Name = "Defecto";
                }
                indexes[c] = (*iter).first;
                c++;
        }
}
//---------------------------------------------------------------------------

void DefectoMenuOrdenar(TTable *tabla, TMenuItem *MenuItemOrdenar)
{
        TMenuItem *menuitem = (TMenuItem *)MenuItemOrdenar->FindComponent("Defecto");
        menuitem->Checked = true;
        tabla->IndexName = indexes[menuitem->Tag];
}
//---------------------------------------------------------------------------

void SetearMenuOrdenar(TTable *tabla, TMenuItem *menuitem)
{
        menuitem->Checked = true;
        tabla->IndexName = indexes[menuitem->Tag];
}
//---------------------------------------------------------------------------

bool BuscarClave(TTable *table, AnsiString campos, Variant value1, ...)
{
        int cantidad = 1;

        for (int c = 1; c <= campos.Length(); c++)
        {
                if (campos[c] == ';') cantidad++;
        }
        TLocateOptions Opts;
        Opts.Clear();
        Variant *locvalues = new Variant[cantidad];

        va_list ap;
        va_start(ap, value1);
        locvalues[0] = value1;
        for (int c = 1; c < cantidad; c++)
        {
                locvalues[c] = va_arg(ap, Variant);
        }
        bool retorno;
        if (table->Locate(campos, VarArrayOf(locvalues, cantidad - 1), Opts))
        {
                retorno = true;
        }
        else
        {
                retorno = false;
        }
        delete[] locvalues;
        return retorno;
}
//---------------------------------------------------------------------------

void EliminarDirectorio(AnsiString directorio)
{
        WIN32_FIND_DATA data;
        HANDLE find;
        AnsiString files, file, tmp;

        files = directorio + "\\*";
        find = FindFirstFile(files.c_str(), &data);
        if (find == INVALID_HANDLE_VALUE) return;
        do
        {
                tmp = data.cFileName;
                if (tmp == "." || tmp == "..") continue;
                file = directorio + "\\" + tmp;
                if (! (DeleteFile(file.c_str()) || RemoveDirectory(file.c_str())))
                {
                        EliminarDirectorio(file);
                }
        } while (FindNextFile(find, &data));
        RemoveDirectory(directorio.c_str()); // No lo borra
}
//---------------------------------------------------------------------------

AnsiString MonedaANumero(AnsiString texto)
{
        int pos;

        texto = texto.Trim();
        texto.Delete(1, 1); // borra signo $
        while ((pos = texto.Pos(",")) != 0)
        {
                texto.Delete(pos, 1);
        }
        return texto;
}
//---------------------------------------------------------------------------

bool CrearLockFile()
{
        AnsiString fichero = "Ventas2012.lck";
        if (! access(fichero.c_str(), 00) && ! DeleteFile(fichero.c_str()))
        {
                return false;
        }
        else
        {
                static ofstream lockfile;
                lockfile.open(fichero.c_str(), ofstream::out);
                return true;
        }
}
//---------------------------------------------------------------------------

AnsiString barras(AnsiString string)
{
        for (int c = 1; c < string.Length(); c++)
        {
                if (string[c] == '\n') break;
                if (string[c] == '\\')
                {
                        string.Insert("\\",c+1);
                        c++;
                }
        }
        return string;
}
//---------------------------------------------------------------------------

AnsiString FechaHoraBackup()
{
        return Date().FormatString("yymmdd") + Time().FormatString("hhnnss");
}
//---------------------------------------------------------------------------

bool BuscarElemento(TTable *table, AnsiString campo, AnsiString texto)
{
        TBookmark posicion = table->GetBookmark();
        table->DisableControls();

        table->First();
        do
        {
                if (table->FieldValues[campo] == texto)
                {
                        table->EnableControls();
                        table->FreeBookmark(posicion);
                        return true;
                }
                table->Next();
        } while (! table->Eof);
        table->EnableControls();
        table->GotoBookmark(posicion);
        table->FreeBookmark(posicion);
        return false;
}
//---------------------------------------------------------------------------

AnsiString Mayus(AnsiString str)
{
        str = str.LowerCase();
        AnsiString tmp(str);
        int p;
        if (str.IsEmpty()) return str;
        if (isalpha(str[1]))
        {
                str[1] = _toupper(str[1]);
        }
        while ((p = tmp.Pos(" ")) != 0)
        {
                tmp[p] = '_';
                if (isalpha(str[p + 1]))
                {
                        str[p + 1] = _toupper(str[p + 1]);
                }
        }
        return str;
}
//---------------------------------------------------------------------------

AnsiString GetTempDir()
{
        const DWORD tam_buffer = 1000;
        char buffer[tam_buffer];

        GetTempPath(tam_buffer, buffer);
        return AnsiString(buffer);
}
//---------------------------------------------------------------------------

TDate StringToDate(AnsiString str)
{
        int dia, mes, ano;

        ano = str.SubString(1,4).ToIntDef(0);
        mes = str.SubString(5,2).ToIntDef(0);
        dia = str.SubString(7,2).ToIntDef(0);
        return TDate(ano, mes, dia);
}
//---------------------------------------------------------------------------

AnsiString SinGuiones(AnsiString s)
{
        return AnsiReplaceStr(s, "-", "");
}
//---------------------------------------------------------------------------


