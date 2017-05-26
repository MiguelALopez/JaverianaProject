DROP TABLE IF EXISTS usuario CASCADE;
CREATE TABLE usuario(
    usuario_cedula              VARCHAR NOT NULL,
    usuario_nombre              VARCHAR NOT NULL,
    usuario_apellido            VARCHAR NOT NULL,
    usuario_password            VARCHAR NOT NULL,
    usuario_fecha_nacimiento    DATE    NOT NULL,
    usuario_telefono            VARCHAR NOT NULL,
    usuario_direccion           VARCHAR NOT NULL,
    usuario_sexo                VARCHAR NOT NULL,
    usuario_estado_civil        VARCHAR NOT NULL,
    usuario_correo              VARCHAR NOT NULL,
    usuario_ingreso             DECIMAL NOT NULL,
    PRIMARY KEY(usuario_cedula),
);


DROP TABLE IF EXISTS fondo CASCADE;
CREATE TABLE fondo(
    fondo_id                     VARCHAR NOT NULL SERIAL,
    fondo_smmlv                  DECIMAL NOT NULL,
    PRIMARY KEY(fondo_id),
);

DROP TABLE IF EXISTS notificacion CASCADE;
CREATE TABLE notificacion(
    notificacion_id             VARCHAR NOT NULL SERIAL,
    notificacion_titulo         VARCHAR NOT NULL,
    notificacion_descripción    VARCHAR NOT NULL,
    usuario_cedula              VARCHAR NOT NULL,
    PRIMARY KEY(notificacion_id),
    FOREIGN KEY(usuario_cedula) REFERENCES usuario(usuario_cedula)
);

DROP TABLE IF EXISTS credito CASCADE;
CREATE TABLE credito(
    credito_ref                 VARCHAR NOT NULL SERIAL,
    credito_ingreso_familiar    DECIMAL NOT NULL,
    credito_nombre_empresa      VARCHAR NOT NULL,
    credito_telefono_empresa    VARCHAR NOT NULL,
    credito_tiempo_laborando    DECIMAL NOT NULL,
    credito_valor_prestamo      DECIMAL NOT NULL,
    credito_total_gastos        DECIMAL NOT NULL,
    credito_plazo               DECIMAL NOT NULL,
    credito_numero_meses        DECIMAL NOT NULL,
    credito_valor_aprobacion    DECIMAL NOT NULL,
    credito_fecha               DATE    NOT NULL,
    credito_estado              VARCHAR NOT NULL,
    usuario_cedula              VARCHAR NOT NULL,
    fondo_id                    VARCHAR NOT NULL,
    PRIMARY KEY(credito_ref),
    FOREIGN KEY(usuario_cedula) REFERENCES usuario(usuario_cedula),
    FOREIGN KEY(fondo_id) REFERENCES fondo(fondo_id)
);

DROP TABLE IF EXISTS auxilio CASCADE;
CREATE TABLE auxilio(
    auxilio_ref                 VARCHAR NOT NULL SERIAL,
    auxilio_tipo                VARCHAR NOT NULL,
    auxilio_valor               DECIMAL NOT NULL,
    auxilio_valor_aprobacion    VARCHAR NOT NULL,
    auxilio_fecha               DATE    NOT NULL,
    auxilio_estado              VARCHAR NOT NULL,
    usuario_cedula              VARCHAR NOT NULL,
    fondo_id                    VARCHAR NOT NULL,
    PRIMARY KEY(credito_ref),
    FOREIGN KEY(usuario_cedula) REFERENCES usuario(usuario_cedula),
    FOREIGN KEY(fondo_id) REFERENCES fondo(fondo_id)
);

DROP TABLE IF EXISTS ahorro CASCADE;
CREATE TABLE ahorro(
    ahorro_ref                   VARCHAR NOT NULL SERIAL,
    ahorro_valor                 VARCHAR NOT NULL,
    ahorro_fecha                 DATE    NOT NULL,
    usuario_cedula               VARCHAR NOT NULL,
    fondo_id                     VARCHAR NOT NULL,
    PRIMARY KEY(ahorro_ref),
    FOREIGN KEY(usuario_cedula) REFERENCES usuario(usuario_cedula),
    FOREIGN KEY(fondo_id) REFERENCES fondo(fondo_id)
);


DROP TABLE IF EXISTS propiedades_ahorro CASCADE;
CREATE TABLE propiedades_ahorro(
    propiedades_ahorro_id           VARCHAR NOT NULL SERIAL,
    propiedades_ahorro_tasa_max     DECIMAL NOT NULL,
    propiedades_ahorro_tasa_min     DECIMAL NOT NULL,
    PRIMARY KEY(propiedades_ahorro_id)
);

DROP TABLE IF EXISTS propiedades_credito CASCADE;
CREATE TABLE propiedades_credito(
    propiedades_credito_id                  VARCHAR NOT NULL SERIAL,
    propiedades_credito_tiempo_max          DECIMAL NOT NULL,
    propiedades_credito_tasa                DECIMAL NOT NULL,
    propiedades_credito_antiguedad          DECIMAL NOT NULL,
    propiedades_credito_monto_max           DECIMAL NOT NULL,
    propiedades_credito_administracion      DECIMAL NOT NULL,
    propiedades_credito_seguro              DECIMAL NOT NULL,
    propiedades_credito_valor_plataforma    DECIMAL NOT NULL,
    PRIMARY KEY(propiedades_credito_id)
);

DROP TABLE IF EXISTS propiedades_auxilio CASCADE;
CREATE TABLE propiedades_auxilio(
    propiedades_auxilio_id                  VARCHAR NOT NULL,
    propiedades_auxilio_tasa_calamidad      DECIMAL NOT NULL,
    propiedades_auxilio_tasa_educacion      DECIMAL NOT NULL,
    propiedades_auxilio_aux_max_calamidad   DECIMAL NOT NULL,
    propiedades_auxilio_valor_max_auxilio   DECIMAL NOT NULL,
    PRIMARY KEY(propiedades_auxilio_id)
);