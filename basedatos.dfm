object BD: TBD
  OldCreateOrder = False
  Left = 201
  Top = 138
  Height = 777
  Width = 750
  object TableClientes: TTable
    AfterPost = FlushDataSet
    AfterDelete = FlushDataSet
    DatabaseName = 'bd2'
    Exclusive = True
    FieldDefs = <
      item
        Name = 'NumeroCliente'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'Fecha'
        Attributes = [faRequired]
        DataType = ftDate
      end
      item
        Name = 'NombreCliente'
        Attributes = [faRequired]
        DataType = ftString
        Size = 30
      end
      item
        Name = 'Direccion'
        DataType = ftString
        Size = 30
      end
      item
        Name = 'Localidad'
        DataType = ftString
        Size = 20
      end
      item
        Name = 'Provincia'
        DataType = ftString
        Size = 20
      end
      item
        Name = 'Telefono1'
        DataType = ftString
        Size = 20
      end
      item
        Name = 'Telefono2'
        DataType = ftString
        Size = 20
      end
      item
        Name = 'Fax'
        DataType = ftString
        Size = 20
      end
      item
        Name = 'Movil'
        DataType = ftString
        Size = 20
      end
      item
        Name = 'E-mail'
        DataType = ftString
        Size = 30
      end
      item
        Name = 'NombreNegocio'
        DataType = ftString
        Size = 30
      end
      item
        Name = 'TipoNegocio'
        DataType = ftString
        Size = 20
      end
      item
        Name = 'NombreFactura'
        DataType = ftString
        Size = 30
      end
      item
        Name = 'PosicionIVA'
        Attributes = [faRequired]
        DataType = ftString
        Size = 30
      end
      item
        Name = 'CUIT'
        DataType = ftString
        Size = 14
      end
      item
        Name = 'FormaPago'
        DataType = ftString
        Size = 20
      end
      item
        Name = 'Descuento'
        DataType = ftFloat
      end
      item
        Name = 'NumeroRegistrosCC'
        DataType = ftInteger
      end
      item
        Name = 'SaldoCC'
        DataType = ftCurrency
      end
      item
        Name = 'NombreAFIP'
        DataType = ftString
        Size = 60
      end>
    IndexDefs = <
      item
        Name = 'ISSaldoCC'
        Fields = 'SaldoCC'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISDescuento'
        Fields = 'Descuento'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISFormaPago'
        Fields = 'FormaPago'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISPosicionIVA'
        Fields = 'PosicionIVA'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISNombreFactura'
        Fields = 'NombreFactura'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISTipoNegocio'
        Fields = 'TipoNegocio'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISNombreNegocio'
        Fields = 'NombreNegocio'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISProvincia'
        Fields = 'Provincia'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISLocalidad'
        Fields = 'Localidad'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISDireccion'
        Fields = 'Direccion'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISNombreCliente'
        Fields = 'NombreCliente'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISFecha'
        Fields = 'Fecha'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISNumeroCliente'
        Fields = 'NumeroCliente'
        Options = [ixCaseInsensitive]
      end>
    StoreDefs = True
    TableName = 'clientes.db'
    Left = 72
    Top = 24
    object TableClientesNumeroCliente: TIntegerField
      FieldName = 'NumeroCliente'
      Required = True
    end
    object TableClientesFecha: TDateField
      FieldName = 'Fecha'
      Required = True
    end
    object TableClientesNombreCliente: TStringField
      FieldName = 'NombreCliente'
      Required = True
      Size = 30
    end
    object TableClientesDireccion: TStringField
      FieldName = 'Direccion'
      Size = 30
    end
    object TableClientesLocalidad: TStringField
      FieldName = 'Localidad'
    end
    object TableClientesProvincia: TStringField
      FieldName = 'Provincia'
    end
    object TableClientesTelefono1: TStringField
      FieldName = 'Telefono1'
    end
    object TableClientesTelefono2: TStringField
      FieldName = 'Telefono2'
    end
    object TableClientesFax: TStringField
      FieldName = 'Fax'
    end
    object TableClientesMovil: TStringField
      FieldName = 'Movil'
    end
    object TableClientesEmail: TStringField
      FieldName = 'E-mail'
      Size = 30
    end
    object TableClientesNombreNegocio: TStringField
      FieldName = 'NombreNegocio'
      Size = 30
    end
    object TableClientesTipoNegocio: TStringField
      FieldName = 'TipoNegocio'
    end
    object TableClientesNombreFactura: TStringField
      FieldName = 'NombreFactura'
      Size = 30
    end
    object TableClientesPosicionIVA: TStringField
      FieldName = 'PosicionIVA'
      Required = True
      Size = 30
    end
    object TableClientesCUIT: TStringField
      FieldName = 'CUIT'
      EditMask = '##-########-#;1;_'
      Size = 14
    end
    object TableClientesFormaPago: TStringField
      FieldName = 'FormaPago'
    end
    object TableClientesDescuento: TFloatField
      FieldName = 'Descuento'
    end
    object TableClientesNumeroRegistrosCC: TIntegerField
      FieldName = 'NumeroRegistrosCC'
    end
    object TableClientesSaldoCC: TCurrencyField
      FieldName = 'SaldoCC'
    end
  end
  object TableProductos: TTable
    AfterPost = FlushDataSet
    AfterDelete = FlushDataSet
    OnPostError = TableProductosPostError
    DatabaseName = 'bd2'
    Exclusive = True
    FieldDefs = <
      item
        Name = 'CodigoProducto'
        Attributes = [faRequired]
        DataType = ftString
        Size = 20
      end
      item
        Name = 'Fecha'
        Attributes = [faRequired]
        DataType = ftDate
      end
      item
        Name = 'Descripcion'
        Attributes = [faRequired]
        DataType = ftString
        Size = 30
      end
      item
        Name = 'Familia'
        DataType = ftString
        Size = 40
      end
      item
        Name = 'Unidad'
        DataType = ftString
        Size = 10
      end
      item
        Name = 'Precio1'
        Attributes = [faRequired]
        DataType = ftCurrency
      end
      item
        Name = 'Precio2'
        Attributes = [faRequired]
        DataType = ftCurrency
      end
      item
        Name = 'Precio3'
        Attributes = [faRequired]
        DataType = ftCurrency
      end
      item
        Name = 'Gramos'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'Stock'
        DataType = ftInteger
      end>
    IndexDefs = <
      item
        Name = 'ISPrecio3'
        Fields = 'Precio3'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISPrecio2'
        Fields = 'Precio2'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISPrecio1'
        Fields = 'Precio1'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISUnidad'
        Fields = 'Unidad'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISFamilia'
        Fields = 'Familia'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISDescripcion'
        Fields = 'Descripcion'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISFecha'
        Fields = 'Fecha'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISCodigoProducto'
        Fields = 'CodigoProducto'
        Options = [ixCaseInsensitive]
      end>
    StoreDefs = True
    TableName = 'productos.DB'
    Left = 232
    Top = 24
    object TableProductosCodigoProducto: TStringField
      FieldName = 'CodigoProducto'
      Required = True
    end
    object TableProductosFecha: TDateField
      FieldName = 'Fecha'
      Required = True
    end
    object TableProductosDescripcion: TStringField
      FieldName = 'Descripcion'
      Required = True
      Size = 30
    end
    object TableProductosFamilia: TStringField
      DisplayWidth = 40
      FieldName = 'Familia'
      Size = 40
    end
    object TableProductosUnidad: TStringField
      FieldName = 'Unidad'
      Size = 10
    end
    object TableProductosPrecio1: TCurrencyField
      FieldName = 'Precio1'
      Required = True
    end
    object TableProductosPrecio2: TCurrencyField
      FieldName = 'Precio2'
      Required = True
    end
    object TableProductosPrecio3: TCurrencyField
      FieldName = 'Precio3'
      Required = True
    end
    object TableProductosGramos: TIntegerField
      FieldName = 'Gramos'
      Required = True
    end
    object TableProductosStock: TIntegerField
      FieldName = 'Stock'
    end
  end
  object TableDocumentos: TTable
    AfterPost = FlushDataSet
    AfterDelete = FlushDataSet
    DatabaseName = 'bd2'
    Exclusive = True
    FieldDefs = <
      item
        Name = 'TipoDocumento'
        Attributes = [faRequired]
        DataType = ftSmallint
      end
      item
        Name = 'NumeroDocumento'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'NumeroCliente'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'Fecha'
        Attributes = [faRequired]
        DataType = ftDate
      end
      item
        Name = 'Hora'
        Attributes = [faRequired]
        DataType = ftTime
      end
      item
        Name = 'NombreFactura'
        Attributes = [faRequired]
        DataType = ftString
        Size = 30
      end
      item
        Name = 'Subtotal'
        Attributes = [faRequired]
        DataType = ftCurrency
      end
      item
        Name = 'Descuento'
        Attributes = [faRequired]
        DataType = ftFloat
      end
      item
        Name = 'DescuentoTotal'
        Attributes = [faRequired]
        DataType = ftCurrency
      end
      item
        Name = 'Subtotal2'
        Attributes = [faRequired]
        DataType = ftCurrency
      end
      item
        Name = 'IVA'
        Attributes = [faRequired]
        DataType = ftFloat
      end
      item
        Name = 'IVATotal'
        Attributes = [faRequired]
        DataType = ftCurrency
      end
      item
        Name = 'Total'
        Attributes = [faRequired]
        DataType = ftCurrency
      end
      item
        Name = 'Estado'
        Attributes = [faRequired]
        DataType = ftSmallint
      end
      item
        Name = 'Direccion'
        DataType = ftString
        Size = 30
      end
      item
        Name = 'Localidad'
        DataType = ftString
        Size = 20
      end
      item
        Name = 'Provincia'
        DataType = ftString
        Size = 20
      end
      item
        Name = 'PosicionIVA'
        Attributes = [faRequired]
        DataType = ftString
        Size = 30
      end
      item
        Name = 'CUIT'
        DataType = ftString
        Size = 14
      end
      item
        Name = 'FormaPago'
        DataType = ftString
        Size = 20
      end
      item
        Name = 'Comunicado'
        DataType = ftMemo
        Size = 1
      end>
    IndexDefs = <
      item
        Name = 'ISFechaHora'
        Fields = 'Fecha;Hora'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISNombreFactura'
        Fields = 'NombreFactura'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISTotal'
        Fields = 'Total'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISEstado'
        Fields = 'Estado'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISTipoNumero'
        Fields = 'TipoDocumento;NumeroDocumento'
        Options = [ixCaseInsensitive]
      end>
    IndexFieldNames = 'TipoDocumento;NumeroDocumento'
    MasterFields = 'TipoDocumento;NumeroDocumento'
    StoreDefs = True
    TableName = 'documentos.DB'
    Left = 72
    Top = 88
    object TableDocumentosTipoDocumento: TSmallintField
      FieldName = 'TipoDocumento'
      Required = True
      OnGetText = TableDocumentosTipoDocumentoGetText
    end
    object TableDocumentosNumeroDocumento: TIntegerField
      FieldName = 'NumeroDocumento'
      Required = True
    end
    object TableDocumentosNumeroCliente: TIntegerField
      FieldName = 'NumeroCliente'
      Required = True
    end
    object TableDocumentosFecha: TDateField
      FieldName = 'Fecha'
      Required = True
    end
    object TableDocumentosHora: TTimeField
      FieldName = 'Hora'
      Required = True
    end
    object TableDocumentosNombreFactura: TStringField
      FieldName = 'NombreFactura'
      Required = True
      Size = 30
    end
    object TableDocumentosSubtotal: TCurrencyField
      FieldName = 'Subtotal'
      Required = True
    end
    object TableDocumentosDescuento: TFloatField
      FieldName = 'Descuento'
      Required = True
    end
    object TableDocumentosDescuentoTotal: TCurrencyField
      FieldName = 'DescuentoTotal'
      Required = True
    end
    object TableDocumentosSubtotal2: TCurrencyField
      FieldName = 'Subtotal2'
      Required = True
    end
    object TableDocumentosIVA: TFloatField
      FieldName = 'IVA'
      Required = True
    end
    object TableDocumentosIVATotal: TCurrencyField
      FieldName = 'IVATotal'
      Required = True
    end
    object TableDocumentosTotal: TCurrencyField
      FieldName = 'Total'
      Required = True
    end
    object TableDocumentosEstado: TSmallintField
      FieldName = 'Estado'
      Required = True
      OnGetText = TableDocumentosEstadoGetText
    end
    object TableDocumentosDireccion: TStringField
      FieldName = 'Direccion'
      Size = 40
    end
    object TableDocumentosLocalidad: TStringField
      FieldName = 'Localidad'
    end
    object TableDocumentosProvincia: TStringField
      FieldName = 'Provincia'
    end
    object TableDocumentosPosicionIVA: TStringField
      FieldName = 'PosicionIVA'
      Required = True
      Size = 30
    end
    object TableDocumentosCUIT: TStringField
      FieldName = 'CUIT'
      Size = 14
    end
    object TableDocumentosFormaPago: TStringField
      FieldName = 'FormaPago'
    end
    object TableDocumentosComunicado: TMemoField
      FieldName = 'Comunicado'
      BlobType = ftMemo
      Size = 1
    end
  end
  object TableDocumentosDetalles: TTable
    AfterPost = FlushDataSet
    AfterDelete = FlushDataSet
    DatabaseName = 'bd2'
    Exclusive = True
    FieldDefs = <
      item
        Name = 'TipoDocumento'
        Attributes = [faRequired]
        DataType = ftSmallint
      end
      item
        Name = 'NumeroDocumento'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'NumeroRenglon'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'Cantidad'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'CodigoProducto'
        Attributes = [faRequired]
        DataType = ftString
        Size = 20
      end
      item
        Name = 'Unidad'
        DataType = ftString
        Size = 10
      end
      item
        Name = 'Descripcion'
        Attributes = [faRequired]
        DataType = ftString
        Size = 30
      end
      item
        Name = 'Precio'
        Attributes = [faRequired]
        DataType = ftCurrency
      end
      item
        Name = 'SinCargo'
        Attributes = [faRequired]
        DataType = ftBoolean
      end
      item
        Name = 'Importe'
        Attributes = [faRequired]
        DataType = ftCurrency
      end>
    IndexFieldNames = 'TipoDocumento;NumeroDocumento;NumeroRenglon'
    MasterFields = 'TipoDocumento;NumeroDocumento'
    MasterSource = DataSourceDocumentos
    StoreDefs = True
    TableName = 'documentosdetalles.DB'
    Left = 232
    Top = 96
    object TableDocumentosDetallesTipoDocumento: TSmallintField
      FieldName = 'TipoDocumento'
      Required = True
    end
    object TableDocumentosDetallesNumeroDocumento: TIntegerField
      FieldName = 'NumeroDocumento'
      Required = True
    end
    object TableDocumentosDetallesNumeroRenglon: TIntegerField
      FieldName = 'NumeroRenglon'
      Required = True
    end
    object TableDocumentosDetallesCantidad: TIntegerField
      FieldName = 'Cantidad'
      Required = True
    end
    object TableDocumentosDetallesCodigoProducto: TStringField
      FieldName = 'CodigoProducto'
      Required = True
    end
    object TableDocumentosDetallesUnidad: TStringField
      FieldName = 'Unidad'
      Size = 10
    end
    object TableDocumentosDetallesDescripcion: TStringField
      FieldName = 'Descripcion'
      Required = True
      Size = 30
    end
    object TableDocumentosDetallesPrecio: TCurrencyField
      FieldName = 'Precio'
      Required = True
    end
    object TableDocumentosDetallesSinCargo: TBooleanField
      FieldName = 'SinCargo'
      Required = True
    end
    object TableDocumentosDetallesImporte: TCurrencyField
      FieldName = 'Importe'
      Required = True
    end
  end
  object TableVentasDiario: TTable
    AfterPost = FlushDataSet
    AfterDelete = FlushDataSet
    DatabaseName = 'bd2'
    Exclusive = True
    FieldDefs = <
      item
        Name = 'Fecha'
        Attributes = [faRequired]
        DataType = ftDate
      end
      item
        Name = 'MontoRemitos'
        Attributes = [faRequired]
        DataType = ftCurrency
      end
      item
        Name = 'MontoFacturas'
        Attributes = [faRequired]
        DataType = ftCurrency
      end
      item
        Name = 'MontoTotal'
        Attributes = [faRequired]
        DataType = ftCurrency
      end>
    IndexDefs = <
      item
        Name = 'ISMontoTotal'
        Fields = 'MontoTotal'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISMontoFacturas'
        Fields = 'MontoFacturas'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISMontoRemitos'
        Fields = 'MontoRemitos'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISFecha'
        Fields = 'Fecha'
        Options = [ixCaseInsensitive]
      end>
    StoreDefs = True
    TableName = 'ventasdiario.DB'
    Left = 232
    Top = 152
    object TableVentasDiarioFecha: TDateField
      FieldName = 'Fecha'
      Required = True
    end
    object TableVentasDiarioMontoRemitos: TCurrencyField
      FieldName = 'MontoRemitos'
      Required = True
    end
    object TableVentasDiarioMontoFacturas: TCurrencyField
      FieldName = 'MontoFacturas'
      Required = True
    end
    object TableVentasDiarioMontoTotal: TCurrencyField
      FieldName = 'MontoTotal'
      Required = True
    end
  end
  object TableCuentasCorrientes: TTable
    BeforeEdit = TableCuentasCorrientesBeforeEdit
    AfterPost = TableCuentasCorrientesAfterPost
    AfterDelete = TableCuentasCorrientesAfterDelete
    DatabaseName = 'bd2'
    Exclusive = True
    FieldDefs = <
      item
        Name = 'NumeroCliente'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'NumeroRegistro'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'Fecha'
        Attributes = [faRequired]
        DataType = ftDate
      end
      item
        Name = 'Hora'
        Attributes = [faRequired]
        DataType = ftTime
      end
      item
        Name = 'Debe'
        Attributes = [faRequired]
        DataType = ftCurrency
      end
      item
        Name = 'Haber'
        Attributes = [faRequired]
        DataType = ftCurrency
      end
      item
        Name = 'SaldoParcial'
        Attributes = [faRequired]
        DataType = ftCurrency
      end
      item
        Name = 'TipoDocumento'
        Attributes = [faRequired]
        DataType = ftSmallint
      end
      item
        Name = 'NumeroDocumento'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'Observacion'
        DataType = ftMemo
        Size = 1
      end>
    IndexFieldNames = 'NumeroCliente;NumeroRegistro'
    MasterFields = 'NumeroCliente'
    MasterSource = DataSourceClientes
    StoreDefs = True
    TableName = 'cuentascorrientes.DB'
    Left = 72
    Top = 152
    object TableCuentasCorrientesTipoDocumento: TSmallintField
      FieldName = 'TipoDocumento'
      Required = True
      OnGetText = TableCuentasCorrientesTipoDocumentoGetText
    end
    object TableCuentasCorrientesNumeroDocumento: TIntegerField
      FieldName = 'NumeroDocumento'
      Required = True
      OnGetText = TableCuentasCorrientesNumeroDocumentoGetText
    end
    object TableCuentasCorrientesObservacion: TMemoField
      FieldName = 'Observacion'
      OnGetText = TableCuentasCorrientesObservacionGetText
      OnSetText = TableCuentasCorrientesObservacionSetText
      BlobType = ftMemo
      Size = 1
    end
    object TableCuentasCorrientesNumeroCliente: TIntegerField
      FieldName = 'NumeroCliente'
      Required = True
    end
    object TableCuentasCorrientesNumeroRegistro: TIntegerField
      FieldName = 'NumeroRegistro'
      Required = True
    end
    object TableCuentasCorrientesFecha: TDateField
      FieldName = 'Fecha'
      Required = True
    end
    object TableCuentasCorrientesHora: TTimeField
      FieldName = 'Hora'
      Required = True
    end
    object TableCuentasCorrientesDebe: TCurrencyField
      FieldName = 'Debe'
      Required = True
    end
    object TableCuentasCorrientesHaber: TCurrencyField
      FieldName = 'Haber'
      Required = True
    end
    object TableCuentasCorrientesSaldoParcial: TCurrencyField
      FieldName = 'SaldoParcial'
      Required = True
    end
  end
  object TableVentasAnual: TTable
    AfterPost = FlushDataSet
    AfterDelete = FlushDataSet
    DatabaseName = 'bd2'
    Exclusive = True
    FieldDefs = <
      item
        Name = 'Ano'
        Attributes = [faRequired]
        DataType = ftSmallint
      end
      item
        Name = 'MontoRemitos'
        Attributes = [faRequired]
        DataType = ftCurrency
      end
      item
        Name = 'MontoFacturas'
        Attributes = [faRequired]
        DataType = ftCurrency
      end
      item
        Name = 'MontoTotal'
        Attributes = [faRequired]
        DataType = ftCurrency
      end>
    IndexDefs = <
      item
        Name = 'ISAno'
        Fields = 'Ano'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISMontoRemitos'
        Fields = 'MontoRemitos'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISMontoFacturas'
        Fields = 'MontoFacturas'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISMontoTotal'
        Fields = 'MontoTotal'
        Options = [ixCaseInsensitive]
      end>
    StoreDefs = True
    TableName = 'ventasanual.DB'
    Left = 232
    Top = 216
    object TableVentasAnualAno: TSmallintField
      FieldName = 'Ano'
      Required = True
    end
    object TableVentasAnualMontoRemitos: TCurrencyField
      FieldName = 'MontoRemitos'
      Required = True
    end
    object TableVentasAnualMontoFacturas: TCurrencyField
      FieldName = 'MontoFacturas'
      Required = True
    end
    object TableVentasAnualMontoTotal: TCurrencyField
      FieldName = 'MontoTotal'
      Required = True
    end
  end
  object TableVentasMensual: TTable
    AfterPost = FlushDataSet
    AfterDelete = FlushDataSet
    DatabaseName = 'bd2'
    Exclusive = True
    FieldDefs = <
      item
        Name = 'Ano'
        Attributes = [faRequired]
        DataType = ftSmallint
      end
      item
        Name = 'Mes'
        Attributes = [faRequired]
        DataType = ftSmallint
      end
      item
        Name = 'MontoRemitos'
        Attributes = [faRequired]
        DataType = ftCurrency
      end
      item
        Name = 'MontoFacturas'
        Attributes = [faRequired]
        DataType = ftCurrency
      end
      item
        Name = 'MontoTotal'
        Attributes = [faRequired]
        DataType = ftCurrency
      end>
    IndexDefs = <
      item
        Name = 'ISAnoMes'
        Fields = 'Ano;Mes'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISMontoTotal'
        Fields = 'MontoTotal'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISMontoFacturas'
        Fields = 'MontoFacturas'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISMontoRemitos'
        Fields = 'MontoRemitos'
        Options = [ixCaseInsensitive]
      end>
    StoreDefs = True
    TableName = 'ventasmensual.DB'
    Left = 72
    Top = 216
    object TableVentasMensualAno: TSmallintField
      FieldName = 'Ano'
      Required = True
    end
    object TableVentasMensualMes: TSmallintField
      FieldName = 'Mes'
      Required = True
      OnGetText = TableVentasMensualMesGetText
    end
    object TableVentasMensualMontoRemitos: TCurrencyField
      FieldName = 'MontoRemitos'
      Required = True
    end
    object TableVentasMensualMontoFacturas: TCurrencyField
      FieldName = 'MontoFacturas'
      Required = True
    end
    object TableVentasMensualMontoTotal: TCurrencyField
      FieldName = 'MontoTotal'
      Required = True
    end
  end
  object TableLocalidades: TTable
    AfterPost = FlushDataSet
    AfterDelete = FlushDataSet
    DatabaseName = 'bd2'
    Exclusive = True
    FieldDefs = <
      item
        Name = 'Provincia'
        DataType = ftString
        Size = 20
      end
      item
        Name = 'Localidad'
        DataType = ftString
        Size = 20
      end>
    IndexFieldNames = 'Provincia'
    MasterFields = 'Provincia'
    MasterSource = DataSourceProvincias
    StoreDefs = True
    TableName = 'localidades.db'
    Left = 72
    Top = 280
    object TableLocalidadesProvincia: TStringField
      FieldName = 'Provincia'
    end
    object TableLocalidadesLocalidad: TStringField
      FieldName = 'Localidad'
    end
  end
  object TableProvincias: TTable
    AfterPost = FlushDataSet
    AfterDelete = FlushDataSet
    DatabaseName = 'bd2'
    Exclusive = True
    FieldDefs = <
      item
        Name = 'Provincia'
        DataType = ftString
        Size = 20
      end>
    StoreDefs = True
    TableName = 'provincias.db'
    Left = 232
    Top = 280
    object TableProvinciasProvincia: TStringField
      FieldName = 'Provincia'
    end
  end
  object TableTiposNegocios: TTable
    AfterPost = FlushDataSet
    AfterDelete = FlushDataSet
    DatabaseName = 'bd2'
    Exclusive = True
    FieldDefs = <
      item
        Name = 'TipoNegocio'
        DataType = ftString
        Size = 20
      end>
    StoreDefs = True
    TableName = 'tiposnegocios.db'
    Left = 72
    Top = 344
    object TableTiposNegociosTipoNegocio: TStringField
      FieldName = 'TipoNegocio'
    end
  end
  object TableFamilias: TTable
    AfterPost = FlushDataSet
    AfterDelete = FlushDataSet
    DatabaseName = 'bd2'
    Exclusive = True
    FieldDefs = <
      item
        Name = 'Familia'
        DataType = ftString
        Size = 40
      end>
    StoreDefs = True
    TableName = 'familias.db'
    Left = 72
    Top = 408
    object TableFamiliasFamilia: TStringField
      FieldName = 'Familia'
      Size = 40
    end
  end
  object TableUnidades: TTable
    AfterPost = FlushDataSet
    AfterDelete = FlushDataSet
    DatabaseName = 'bd2'
    Exclusive = True
    FieldDefs = <
      item
        Name = 'Unidad'
        DataType = ftString
        Size = 10
      end>
    StoreDefs = True
    TableName = 'unidades.db'
    Left = 232
    Top = 344
    object TableUnidadesUnidad: TStringField
      FieldName = 'Unidad'
      Size = 10
    end
  end
  object DataSourceProductos: TDataSource
    DataSet = TableProductos
    Left = 608
    Top = 24
  end
  object DataSourceClientes: TDataSource
    DataSet = TableClientes
    Left = 448
    Top = 24
  end
  object DataSourceDocumentosDetalles: TDataSource
    DataSet = TableDocumentosDetalles
    Left = 608
    Top = 88
  end
  object DataSourceDocumentos: TDataSource
    DataSet = TableDocumentos
    Left = 448
    Top = 88
  end
  object DataSourceVentasDiario: TDataSource
    DataSet = TableVentasDiario
    Left = 608
    Top = 152
  end
  object DataSourceCuentasCorrientes: TDataSource
    DataSet = TableCuentasCorrientes
    Left = 448
    Top = 152
  end
  object DataSourceVentasAnual: TDataSource
    DataSet = TableVentasAnual
    Left = 608
    Top = 216
  end
  object DataSourceVentasMensual: TDataSource
    DataSet = TableVentasMensual
    Left = 448
    Top = 216
  end
  object DataSourceProvincias: TDataSource
    DataSet = TableProvincias
    Left = 608
    Top = 280
  end
  object DataSourceLocalidades: TDataSource
    DataSet = TableLocalidades
    Left = 448
    Top = 280
  end
  object DataSourceTiposNegocios: TDataSource
    DataSet = TableTiposNegocios
    Left = 448
    Top = 344
  end
  object DataSourceFamilias: TDataSource
    DataSet = TableFamilias
    Left = 448
    Top = 408
  end
  object DataSourceUnidades: TDataSource
    DataSet = TableUnidades
    Left = 608
    Top = 344
  end
  object TableProductosMensual: TTable
    AfterPost = FlushDataSet
    AfterDelete = FlushDataSet
    DatabaseName = 'bd2'
    Exclusive = True
    FieldDefs = <
      item
        Name = 'CodigoProducto'
        Attributes = [faRequired]
        DataType = ftString
        Size = 20
      end
      item
        Name = 'Mes'
        Attributes = [faRequired]
        DataType = ftSmallint
      end
      item
        Name = 'Ano'
        DataType = ftSmallint
      end
      item
        Name = 'CantidadRemito'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'CantidadFactura'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'CantidadTotal'
        Attributes = [faRequired]
        DataType = ftInteger
      end>
    IndexDefs = <
      item
        Name = 'ISAnoMes'
        Fields = 'Mes;Ano'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISCantidadTotal'
        Fields = 'CantidadTotal'
        Options = [ixCaseInsensitive]
      end>
    StoreDefs = True
    TableName = 'productosmensual.DB'
    Left = 232
    Top = 408
    object TableProductosMensualCodigoProducto: TStringField
      FieldName = 'CodigoProducto'
      Required = True
    end
    object TableProductosMensualMes: TSmallintField
      FieldName = 'Mes'
      Required = True
      OnGetText = TableProductosMensualMesGetText
    end
    object TableProductosMensualAno: TSmallintField
      FieldName = 'Ano'
    end
    object TableProductosMensualCantidadRemito: TIntegerField
      FieldName = 'CantidadRemito'
      Required = True
    end
    object TableProductosMensualCantidadFactura: TIntegerField
      FieldName = 'CantidadFactura'
      Required = True
    end
    object TableProductosMensualCantidadTotal: TIntegerField
      FieldName = 'CantidadTotal'
      Required = True
    end
    object TableProductosMensualDescripcion: TStringField
      FieldKind = fkCalculated
      FieldName = 'Descripcion'
      OnGetText = TableProductosDescripcionGetText
      Size = 30
      Calculated = True
    end
    object TableProductosMensualUnidad: TStringField
      FieldKind = fkCalculated
      FieldName = 'Unidad'
      OnGetText = TableProductosUnidadGetText
      Size = 10
      Calculated = True
    end
  end
  object TableProductosDiario: TTable
    AfterPost = FlushDataSet
    AfterDelete = FlushDataSet
    DatabaseName = 'bd2'
    Exclusive = True
    FieldDefs = <
      item
        Name = 'CodigoProducto'
        Attributes = [faRequired]
        DataType = ftString
        Size = 20
      end
      item
        Name = 'Fecha'
        Attributes = [faRequired]
        DataType = ftDate
      end
      item
        Name = 'CantidadRemito'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'CantidadFactura'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'CantidadTotal'
        Attributes = [faRequired]
        DataType = ftInteger
      end>
    IndexDefs = <
      item
        Name = 'ISCantidadTotal'
        Fields = 'CantidadTotal'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISFecha'
        Fields = 'Fecha'
        Options = [ixCaseInsensitive]
      end>
    StoreDefs = True
    TableName = 'productosdiario.DB'
    Left = 72
    Top = 472
    object TableProductosDiarioCodigoProducto: TStringField
      FieldName = 'CodigoProducto'
      Required = True
    end
    object TableProductosDiarioFecha: TDateField
      FieldName = 'Fecha'
      Required = True
    end
    object TableProductosDiarioCantidadRemito: TIntegerField
      FieldName = 'CantidadRemito'
      Required = True
    end
    object TableProductosDiarioCantidadFactura: TIntegerField
      FieldName = 'CantidadFactura'
      Required = True
    end
    object TableProductosDiarioCantidadTotal: TIntegerField
      FieldName = 'CantidadTotal'
      Required = True
    end
    object TableProductosDiarioDescripcion: TStringField
      FieldKind = fkCalculated
      FieldName = 'Descripcion'
      OnGetText = TableProductosDescripcionGetText
      Size = 30
      Calculated = True
    end
    object TableProductosDiarioUnidad: TStringField
      FieldKind = fkCalculated
      FieldName = 'Unidad'
      OnGetText = TableProductosUnidadGetText
      Size = 10
      Calculated = True
    end
  end
  object TableProductosAnual: TTable
    AfterPost = FlushDataSet
    AfterDelete = FlushDataSet
    DatabaseName = 'bd2'
    Exclusive = True
    FieldDefs = <
      item
        Name = 'CodigoProducto'
        Attributes = [faRequired]
        DataType = ftString
        Size = 20
      end
      item
        Name = 'Ano'
        Attributes = [faRequired]
        DataType = ftSmallint
      end
      item
        Name = 'CantidadRemito'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'CantidadFactura'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'CantidadTotal'
        Attributes = [faRequired]
        DataType = ftInteger
      end>
    IndexDefs = <
      item
        Name = 'ISAno'
        Fields = 'Ano'
        Options = [ixCaseInsensitive]
      end
      item
        Name = 'ISCantidadTotal'
        Fields = 'CantidadTotal'
        Options = [ixCaseInsensitive]
      end>
    StoreDefs = True
    TableName = 'productosanual.DB'
    Left = 72
    Top = 536
    object TableProductosAnualCodigoProducto: TStringField
      FieldName = 'CodigoProducto'
      Required = True
    end
    object TableProductosAnualAno: TSmallintField
      FieldName = 'Ano'
      Required = True
    end
    object TableProductosAnualCantidadRemito: TIntegerField
      FieldName = 'CantidadRemito'
      Required = True
    end
    object TableProductosAnualCantidadFactura: TIntegerField
      FieldName = 'CantidadFactura'
      Required = True
    end
    object TableProductosAnualCantidadTotal: TIntegerField
      FieldName = 'CantidadTotal'
      Required = True
    end
    object TableProductosAnualDescripcion: TStringField
      FieldKind = fkCalculated
      FieldName = 'Descripcion'
      OnGetText = TableProductosDescripcionGetText
      Size = 30
      Calculated = True
    end
    object TableProductosAnualUnidad: TStringField
      FieldKind = fkCalculated
      FieldName = 'Unidad'
      OnGetText = TableProductosUnidadGetText
      Size = 10
      Calculated = True
    end
  end
  object DataSourceProductosMensual: TDataSource
    DataSet = TableProductosMensual
    Left = 608
    Top = 408
  end
  object DataSourceProductosDiario: TDataSource
    DataSet = TableProductosDiario
    Left = 448
    Top = 472
  end
  object DataSourceProductosAnual: TDataSource
    DataSet = TableProductosAnual
    Left = 448
    Top = 536
  end
  object TableNumeracion: TTable
    AfterPost = FlushDataSet
    AfterDelete = FlushDataSet
    DatabaseName = 'bd2'
    Exclusive = True
    FieldDefs = <
      item
        Name = 'NumeroCliente'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'NumeroRemito'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'NumeroFactura'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'NumeroCreditoRemito'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'NumeroCreditoFactura'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'NumeroFacturaElect'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'NumeroCreditoElect'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'NumeroDebitoElect'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'NumeroPedido'
        Attributes = [faRequired]
        DataType = ftInteger
      end>
    StoreDefs = True
    TableName = 'numeracion.DB'
    Left = 232
    Top = 472
    object TableNumeracionNumeroCliente: TIntegerField
      FieldName = 'NumeroCliente'
      Required = True
    end
    object TableNumeracionNumeroRemito: TIntegerField
      FieldName = 'NumeroRemito'
      Required = True
    end
    object TableNumeracionNumeroFactura: TIntegerField
      FieldName = 'NumeroFactura'
      Required = True
    end
    object TableNumeracionNumeroCreditoRemito: TIntegerField
      FieldName = 'NumeroCreditoRemito'
      Required = True
    end
    object TableNumeracionNumeroCreditoFactura: TIntegerField
      FieldName = 'NumeroCreditoFactura'
      Required = True
    end
    object TableNumeracionNumeroFacturaElect: TIntegerField
      FieldName = 'NumeroFacturaElect'
      Required = True
    end
    object TableNumeracionNumeroCreditoElect: TIntegerField
      FieldName = 'NumeroCreditoElect'
      Required = True
    end
    object TableNumeracionNumeroDebitoElect: TIntegerField
      FieldName = 'NumeroDebitoElect'
      Required = True
    end
    object TableNumeracionNumeroPedido: TIntegerField
      FieldName = 'NumeroPedido'
      Required = True
    end
  end
  object DataSourceNumeracion: TDataSource
    DataSet = TableNumeracion
    Left = 608
    Top = 472
  end
  object AbMakeCab: TAbMakeCab
    CompressionType = ctMSZIP
    FolderThreshold = 0
    SetID = 0
    Left = 336
    Top = 8
  end
  object Database: TDatabase
    SessionName = 'Default'
    TransIsolation = tiDirtyRead
    Left = 336
    Top = 80
  end
  object TableFacturaElectronica: TTable
    AfterPost = FlushDataSet
    AfterDelete = FlushDataSet
    DatabaseName = 'bd2'
    Exclusive = True
    FieldDefs = <
      item
        Name = 'TipoDocumento'
        Attributes = [faRequired]
        DataType = ftSmallint
      end
      item
        Name = 'NumeroDocumento'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'Tipo_cbte'
        Attributes = [faRequired]
        DataType = ftSmallint
      end
      item
        Name = 'Cbte_nro'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'Cae'
        Attributes = [faRequired]
        DataType = ftString
        Size = 14
      end
      item
        Name = 'Vto_cae'
        Attributes = [faRequired]
        DataType = ftDate
      end
      item
        Name = 'Obs_afip'
        DataType = ftMemo
        Size = 1
      end
      item
        Name = 'NombreAFIP'
        Attributes = [faRequired]
        DataType = ftString
        Size = 60
      end>
    IndexFieldNames = 'TipoDocumento;NumeroDocumento'
    MasterFields = 'TipoDocumento;NumeroDocumento'
    MasterSource = DataSourceDocumentos
    StoreDefs = True
    TableName = 'facturaelectronica.DB'
    Left = 232
    Top = 536
    object TableFacturaElectronicaTipoDocumento: TSmallintField
      FieldName = 'TipoDocumento'
      Required = True
    end
    object TableFacturaElectronicaNumeroDocumento: TIntegerField
      FieldName = 'NumeroDocumento'
      Required = True
    end
    object TableFacturaElectronicaTipo_cbte: TSmallintField
      FieldName = 'Tipo_cbte'
      Required = True
    end
    object TableFacturaElectronicaCbte_nro: TIntegerField
      FieldName = 'Cbte_nro'
      Required = True
    end
    object TableFacturaElectronicaCae: TStringField
      FieldName = 'Cae'
      Required = True
      Size = 14
    end
    object TableFacturaElectronicaVto_cae: TDateField
      FieldName = 'Vto_cae'
      Required = True
    end
    object TableFacturaElectronicaObs_afip: TMemoField
      FieldName = 'Obs_afip'
      BlobType = ftMemo
      Size = 1
    end
    object TableFacturaElectronicaNombreAFIP: TStringField
      FieldName = 'NombreAFIP'
      Required = True
      Size = 60
    end
  end
  object DataSourceFacturaElectronica: TDataSource
    DataSet = TableFacturaElectronica
    Left = 608
    Top = 536
  end
  object TablePadronAFIP: TTable
    AfterPost = FlushDataSet
    AfterDelete = FlushDataSet
    DatabaseName = 'bd2'
    Exclusive = True
    FieldDefs = <
      item
        Name = 'CUIT'
        Attributes = [faRequired]
        DataType = ftString
        Size = 14
      end
      item
        Name = 'NombreAFIP'
        Attributes = [faRequired]
        DataType = ftString
        Size = 60
      end>
    StoreDefs = True
    TableName = 'padronafip.db'
    Left = 72
    Top = 600
    object TablePadronAFIPCUIT: TStringField
      FieldName = 'CUIT'
      Required = True
      Size = 14
    end
    object TablePadronAFIPNombreAFIP: TStringField
      FieldName = 'NombreAFIP'
      Required = True
      Size = 60
    end
  end
  object DataSourcePadronAFIP: TDataSource
    DataSet = TablePadronAFIP
    Left = 448
    Top = 600
  end
  object TableKilogramosMensual: TTable
    AfterPost = FlushDataSet
    AfterDelete = FlushDataSet
    DatabaseName = 'bd2'
    Exclusive = True
    FieldDefs = <
      item
        Name = 'Mes'
        Attributes = [faRequired]
        DataType = ftSmallint
      end
      item
        Name = 'Ano'
        Attributes = [faRequired]
        DataType = ftSmallint
      end
      item
        Name = 'CantidadRemito'
        Attributes = [faRequired]
        DataType = ftFloat
      end
      item
        Name = 'CantidadFactura'
        Attributes = [faRequired]
        DataType = ftFloat
      end
      item
        Name = 'CantidadTotal'
        Attributes = [faRequired]
        DataType = ftFloat
      end>
    StoreDefs = True
    TableName = 'kilogramosmensual.DB'
    Left = 232
    Top = 600
    object TableKilogramosMensualMes: TSmallintField
      FieldName = 'Mes'
      Required = True
      OnGetText = TableKilogramosMensualMesGetText
    end
    object TableKilogramosMensualAno: TSmallintField
      FieldName = 'Ano'
      Required = True
    end
    object TableKilogramosMensualCantidadRemito: TFloatField
      FieldName = 'CantidadRemito'
      Required = True
      DisplayFormat = '0.00 kg'
    end
    object TableKilogramosMensualCantidadFactura: TFloatField
      FieldName = 'CantidadFactura'
      Required = True
      DisplayFormat = '0.00 kg'
    end
    object TableKilogramosMensualCantidadTotal: TFloatField
      FieldName = 'CantidadTotal'
      Required = True
      DisplayFormat = '0.00 kg'
    end
  end
  object DataSourceKilogramosMensual: TDataSource
    DataSet = TableKilogramosMensual
    Left = 608
    Top = 600
  end
  object DataSourceFacturaTradicional: TDataSource
    DataSet = TableFacturaTradicional
    Left = 448
    Top = 664
  end
  object TableFacturaTradicional: TTable
    AfterPost = FlushDataSet
    AfterDelete = FlushDataSet
    DatabaseName = 'bd2'
    Exclusive = True
    FieldDefs = <
      item
        Name = 'TipoDocumento'
        Attributes = [faRequired]
        DataType = ftSmallint
      end
      item
        Name = 'NumeroDocumento'
        Attributes = [faRequired]
        DataType = ftInteger
      end
      item
        Name = 'Tipo_cbte'
        Attributes = [faRequired]
        DataType = ftSmallint
      end
      item
        Name = 'Cbte_nro'
        Attributes = [faRequired]
        DataType = ftInteger
      end>
    IndexFieldNames = 'TipoDocumento;NumeroDocumento'
    MasterFields = 'TipoDocumento;NumeroDocumento'
    MasterSource = DataSourceDocumentos
    StoreDefs = True
    TableName = 'facturatradicional.db'
    Left = 72
    Top = 664
    object TableFacturaTradicionalTipoDocumento: TSmallintField
      FieldName = 'TipoDocumento'
      Required = True
    end
    object TableFacturaTradicionalNumeroDocumento: TIntegerField
      FieldName = 'NumeroDocumento'
      Required = True
    end
    object TableFacturaTradicionalTipo_cbte: TSmallintField
      FieldName = 'Tipo_cbte'
      Required = True
    end
    object TableFacturaTradicionalCbte_nro: TIntegerField
      FieldName = 'Cbte_nro'
      Required = True
    end
  end
end
