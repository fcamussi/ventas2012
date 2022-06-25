//---------------------------------------------------------------------------

#ifndef auxiliarH
#define auxiliarH
//---------------------------------------------------------------------------

#include <map.h>
#include <Menus.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <DBTables.hpp>
//---------------------------------------------------------------------------

typedef map<AnsiString,AnsiString> ListaMenuOrdenar;

//---------------------------------------------------------------------------


void CrearMenuOrdenar(ListaMenuOrdenar lista, AnsiString defecto,
                      TTable *tabla, TMenuItem *MenuItemOrdenar,
                      void __fastcall (__closure *funcion)(TObject *));
void DefectoMenuOrdenar(TTable *tabla, TMenuItem *MenuItemOrdenar);
void SetearMenuOrdenar(TTable *tabla, TMenuItem *menuitem);
bool BuscarClave(TTable *table, AnsiString campos, Variant value1, ...);
bool BuscarElemento(TTable *table, AnsiString campo, AnsiString texto);
void EliminarDirectorio(AnsiString directorio);
AnsiString MonedaANumero(AnsiString texto);
bool CrearLockFile();
AnsiString barras(AnsiString string);
AnsiString FechaHoraBackup();
AnsiString Mayus(AnsiString str);
AnsiString GetTempDir();
TDate StringToDate(AnsiString str);
AnsiString SinGuiones(AnsiString s);

//---------------------------------------------------------------------------
#endif
