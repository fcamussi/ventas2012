//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector.h>
#include <algorithm>
#include <io.h>

#pragma hdrstop

#include "basedatos.h"
#include "archivoclientes.h"
#include "archivoproductos.h"
#include "dialogoproducto.h"
#include "cuentacorriente.h"
#include "facturacion.h"
#include "buscarclientes.h"
#include "buscarproductos.h"
#include "seleccionarcliente.h"
#include "seleccionarproducto.h"
#include "auxiliar.h"
#include "numeracion.h"
#include "configuracion.h"
#include "impresion.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AbBase"
#pragma link "AbBrowse"
#pragma link "AbZBrows"
#pragma link "AbZipper"
#pragma link "AbCabMak"
#pragma link "AbCBrows"
#pragma resource "*.dfm"
TBD *BD;
bool enabledflush = true;

//---------------------------------------------------------------------------
__fastcall TBD::TBD(TComponent* Owner)
        : TDataModule(Owner)
{
}

//---------------------------------------------------------------------------

int TBD::GetBDEError(EDatabaseError *E)
{
        if (E->ClassNameIs("EDBEngineError"))
        {
                EDBEngineError *pDBE = (EDBEngineError *)E;
                return pDBE->Errors[pDBE->ErrorCount - 1]->ErrorCode;
        }
        return -1;
}
//---------------------------------------------------------------------------

void __fastcall TBD::TableProductosPostError(
      TDataSet *DataSet, EDatabaseError *E, TDataAction &Action)
{
        if (GetBDEError(E) == DBIERR_KEYVIOL)
        {
                MessageBox(FormDialogoProducto->Handle, "El código ya existe. "
                           "Seleccione otro.", Application->Title.c_str(),
                           MB_APPLMODAL | MB_OK | MB_ICONERROR);
                Abort();
        }
}
//---------------------------------------------------------------------------

void TBD::ActivarTableCuentasCorrientesAfterPost(bool activar)
{
        if (activar) TableCuentasCorrientes->AfterPost =
                                             TableCuentasCorrientesAfterPost;
        else TableCuentasCorrientes->AfterPost = NULL;
}
//---------------------------------------------------------------------------

void TBD::ActivarTableCuentasCorrientesBeforeEdit(bool activar)
{
        if (activar) TableCuentasCorrientes->BeforeEdit =
                                             TableCuentasCorrientesBeforeEdit;
        else TableCuentasCorrientes->BeforeEdit = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TBD::TableCuentasCorrientesAfterPost(
      TDataSet *DataSet)
{
        FormCuentaCorriente->ActualizarSaldos();
        FormCuentaCorriente->ActualizarCantidadRegistros();
        FlushDataSet(DataSet);
}
//---------------------------------------------------------------------------

void __fastcall TBD::TableCuentasCorrientesObservacionGetText(
      TField *Sender, AnsiString &Text, bool DisplayText)
{
        Text = Sender->AsString;
}
//---------------------------------------------------------------------------

void __fastcall TBD::TableCuentasCorrientesObservacionSetText(
      TField *Sender, const AnsiString Text)
{
        Sender->AsString = Text;
}
//---------------------------------------------------------------------------

void __fastcall TBD::TableCuentasCorrientesTipoDocumentoGetText(
      TField *Sender, AnsiString &Text, bool DisplayText)
{
        if (! TableCuentasCorrientes->IsEmpty())
        {
                int tipodocumento = Sender->AsInteger;
                Text = (tipodocumento < 0? "": FormFacturacion->Documentos(
                                               Sender->AsInteger).c_str());
        }
}
//---------------------------------------------------------------------------

void __fastcall TBD::TableCuentasCorrientesNumeroDocumentoGetText(
      TField *Sender, AnsiString &Text, bool DisplayText)
{
        if (! TableCuentasCorrientes->IsEmpty())
        {
                int numerodocumento = Sender->AsInteger;
                Text = (numerodocumento < 0? "": IntToStr(numerodocumento).c_str());
        }
}
//---------------------------------------------------------------------------

void __fastcall TBD::TableDocumentosTipoDocumentoGetText(
      TField *Sender, AnsiString &Text, bool DisplayText)
{
        if (! TableDocumentos->IsEmpty())
        {
                int tipodocumento = Sender->AsInteger;
                Text = (tipodocumento < 0? "": FormFacturacion->Documentos(
                                                    Sender->AsInteger).c_str());
        }
}
//---------------------------------------------------------------------------

void __fastcall TBD::TableCuentasCorrientesBeforeEdit(
      TDataSet *DataSet)
{
        /* NOTA: aca se pueden cargar los montos de los debes
        y los haberes */

        int tipodocumento = DataSet->FieldValues["TipoDocumento"];
        int columna = FormCuentaCorriente->DBGrid->SelectedField->Index;
        int colobs = TableCuentasCorrientes->FieldByName("Observacion")->Index;
        int coldebe = TableCuentasCorrientes->FieldByName("Debe")->Index;
        int colhaber = TableCuentasCorrientes->FieldByName("Haber")->Index;
        double debe = TableCuentasCorrientes->FieldValues["Debe"];
        double haber = TableCuentasCorrientes->FieldValues["Haber"];

        if (tipodocumento < 0)
        {
                if (columna == coldebe && haber != 0) Abort();
                if (columna == colhaber && debe != 0) Abort();
        }
        else
        {
                if (columna != colobs)
                {
                        Abort();
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TBD::TableCuentasCorrientesAfterDelete(TDataSet *DataSet)
{
        FormCuentaCorriente->ActualizarCantidadRegistros();
        FlushDataSet(DataSet);
}
//---------------------------------------------------------------------------

void __fastcall TBD::TableDocumentosEstadoGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
        if (! TableDocumentos->IsEmpty())
        {
                int estado = Sender->AsInteger;
                Text = (estado < 0? "": FormFacturacion->Estados(
                                                    Sender->AsInteger).c_str());
        }
}
//---------------------------------------------------------------------------

void __fastcall TBD::TableVentasMensualMesGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
        if (! TableVentasMensual->IsEmpty())
        {
                int mes = Sender->AsInteger;
                if (mes != 0)
                {
                        TDate tmp = StrToDate("1/" + IntToStr(mes) + "/1");
                        Text = tmp.FormatString("mmmm");
                }
        }
}
//---------------------------------------------------------------------------

void TBD::PackParadox(const AnsiString ADatabase, const AnsiString ATable)
{
        CRTblDesc PdxStruct;
        TDatabase *ADB = Session->OpenDatabase(ADatabase);
        try {
                memset((void*) &PdxStruct, 0, sizeof(PdxStruct));
                strcpy(PdxStruct.szTblName, ATable.c_str());
                PdxStruct.bPack = True;
                Check(DbiDoRestructure(ADB->Handle, 1, &PdxStruct,
                      0, 0, 0, False));
        }
        __finally {
                Session->CloseDatabase(ADB);
        }
}
//---------------------------------------------------------------------------

bool TBD::ActivarBaseDatos(bool estado)
{
        TTable *tabla;

        for (int i = 0; i < BD->ComponentCount; i++)
        {
                if (AnsiString(BD->Components[i]->ClassName()) == "TTable")
                {
                        tabla = static_cast<TTable *>(BD->Components[i]);
                        try {
                                tabla->Active = estado;
                                //if (tabla->Active != estado) ShowMessage("Error de mierda 2!!!");;
                        }
                        catch (...) {
                                //ShowMessage("Error de mierda 1!!!");
                                return false;
                        }
                }
        }

        return true;
}
//---------------------------------------------------------------------------

void TBD::Compactar()
{
        TTable *tabla;
        AnsiString dirBD = GetCurrentDir() + "\\datos";

        for (int i = 0; i < BD->ComponentCount; i++)
        {
                if (AnsiString(BD->Components[i]->ClassName()) == "TTable")
                {
                        tabla = static_cast<TTable *>(BD->Components[i]);
                        BD->PackParadox(dirBD, tabla->TableName);
                }
        }
}
//---------------------------------------------------------------------------

bool TBD::CopiaSeguridad(AnsiString dirdest, AnsiString nombre)
{
        TTable *tabla;
        AnsiString cab = dirdest + "\\" + nombre + ".cab";
        AnsiString fichconf = ExtractFileName(FICHCONFIG);
        AnsiString fichcert = FormConfiguracion->Certificado();
        AnsiString fichclave = FormConfiguracion->ClavePrivada();

        if (access(dirdest.c_str(), 06) != 0) return false;

        ReducirBackup(dirdest, FormConfiguracion->BackupsConservar());

        AbMakeCab->FileName = cab;
        AbMakeCab->AddFilesEx("datos\\*.*", "datos\\PDOXUSRS.NET", faAnyFile);
        AbMakeCab->AddFiles(fichconf, faAnyFile);

        if (access("AFIP_XML.log", 04) == 0)
        {
                AbMakeCab->AddFiles("AFIP_XML.log", faAnyFile);
        }
        if (access("AFIP_eventos.log", 04) == 0)
        {
                AbMakeCab->AddFiles("AFIP_eventos.log", faAnyFile);
        }
        if (access(fichcert.c_str(), 04) == 0)
        {
                AbMakeCab->AddFiles(fichcert, faAnyFile);
        }
        if (access(fichclave.c_str(), 04) == 0)
        {
                AbMakeCab->AddFiles(fichclave, faAnyFile);
        }

        AbMakeCab->CloseArchive();

        return true;
}
//---------------------------------------------------------------------------

bool TBD::SetearAlias(AnsiString alias)
{
        TTable *tabla;

        if (! Session->IsAlias(alias))
        {
                AnsiString dir = GetCurrentDir() + "\\datos";
                try {
                        Session->AddStandardAlias(alias, dir, "PARADOX");
                        Session->NetFileDir = dir;
                        //Session->SaveConfigFile();
                }
                catch (...) {
                        return false;
                }
        }

        for (int i = 0; i < BD->ComponentCount; i++)
        {
                if (AnsiString(BD->Components[i]->ClassName()) == "TTable")
                {
                        tabla = static_cast<TTable *>(BD->Components[i]);
                        tabla->DatabaseName = alias;
                }
        }
        Database->DatabaseName = alias; // para transacciones

        return true;
}
//---------------------------------------------------------------------------

void __fastcall TBD::TableProductosMensualMesGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
        if (! TableProductosMensual->IsEmpty())
        {
                int mes = Sender->AsInteger;
                if (mes != 0)
                {
                        TDate tmp = StrToDate("1/" + IntToStr(mes) + "/1");
                        Text = tmp.FormatString("mmmm");
                }
        }
}
//---------------------------------------------------------------------------

void TBD::ReducirBackup(AnsiString dir, int conservar)
{
        WIN32_FIND_DATA data;
        HANDLE find;
        vector<AnsiString> ficheros;
        AnsiString tmp;

        find = FindFirstFile((dir + "\\*.cab").c_str(), &data);
        do
        {
                tmp = data.cFileName;
                if (tmp == "." || tmp == "..") continue;
                ficheros.push_back(tmp);
        } while (FindNextFile(find, &data));

        sort(ficheros.begin(), ficheros.end());

        int borrar = ficheros.size() - conservar;
        if (borrar > 0)
        {
                for (int c = 0; c < borrar; c++)
                {
                       //ShowMessage(ficheros[c]);
                       DeleteFile(dir + "\\" + ficheros[c]);
                }
        }
}
//---------------------------------------------------------------------------

bool TBD::GuardarSaldos()
{
        AnsiString dirdest = FormConfiguracion->CopiaDirectorio();
        Impresion imp;
        
        if (access(dirdest.c_str(), 06) != 0) return false;
        AnsiString nombre = FechaHoraBackup();
        AnsiString dir = dirdest + "\\Saldos";
        MkDir(dir);
        AnsiString fichero = dir + "\\" + nombre + ".txt";
        imp.ExportarSaldos(fichero);

        return true;
}
//---------------------------------------------------------------------------

void __fastcall TBD::TableProductosDescripcionGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
        TTable *table = (TTable *)Sender->DataSet;

        if (! table->IsEmpty())
        {
                AnsiString codigo = table->FieldByName("CodigoProducto")->AsString;
                if (BuscarClave(TableProductos, "CodigoProducto", Variant(codigo)))
                {
                        Text = TableProductos->FieldByName("Descripcion")->AsString;
                }
                else
                {
                        Text = "*";
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TBD::TableProductosUnidadGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
        TTable *table = (TTable *)Sender->DataSet;

        if (! table->IsEmpty())
        {
                AnsiString codigo = table->FieldByName("CodigoProducto")->AsString;
                if (BuscarClave(TableProductos, "CodigoProducto", Variant(codigo)))
                {
                        Text = TableProductos->FieldByName("Unidad")->AsString;
                }
                else
                {
                        Text = "*";
                }
        }
}
//---------------------------------------------------------------------------

void TBD::RefrescarTablas()
{
        for (int i = 0; i < BD->Database->DataSetCount; i++)
        {
                BD->Database->DataSets[i]->Refresh();
        }
}
//---------------------------------------------------------------------------

void TBD::CancelarTablas()
{
        for (int i = 0; i < BD->Database->DataSetCount; i++)
        {
                BD->Database->DataSets[i]->Cancel();
        }
}
//---------------------------------------------------------------------------

void TBD::FlushTablas()
{
        for (int i = 0; i < BD->Database->DataSetCount; i++)
        {
                BD->Database->DataSets[i]->FlushBuffers();
        }
}
//---------------------------------------------------------------------------

void __fastcall TBD::TableKilogramosMensualMesGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
        if (! TableKilogramosMensual->IsEmpty())
        {
                int mes = Sender->AsInteger;
                if (mes != 0)
                {
                        TDate tmp = StrToDate("1/" + IntToStr(mes) + "/1");
                        Text = tmp.FormatString("mmmm");
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TBD::FlushDataSet(TDataSet *DataSet)
{
        TTable *tabla = static_cast<TTable *>(DataSet);
        if (enabledflush) tabla->FlushBuffers();
}
//---------------------------------------------------------------------------

void TBD::FlushEnabled(bool value)
{
        enabledflush = value;
}
//---------------------------------------------------------------------------

