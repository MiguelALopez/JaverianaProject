DROP TABLE IF EXISTS usuario CASCADE;
CREATE TABLE usuario (
	usuario_cedula varchar(20),
	usuario_password varchar(255),
	usuario_nombre varchar(255),
	usuario_apellido varchar(255),
	usuario_fechaNacimiento date,
	usuario_telefono varchar(255),
	usuario_direccion varchar(255),
	usuario_sexo varchar(10),
	usuario_estado_civil varchar(15),
	usuario_correo varchar(255),
	usuario_ingresos int,
	PRIMARY KEY(usuario_cedula)
);

DROP TABLE IF EXISTS fondo CASCADE;
CREATE TABLE fondo(
	fondo_id SERIAL,
	fondo_smmlv int,
	PRIMARY KEY (fondo_id)
);

DROP TABLE IF EXISTS notificacion CASCADE;
CREATE TABLE notificacion(
	notifacacion_id SERIAL,
	notifacion_titulo varchar(20),
	notifacion_descripcion varchar,
	usuario_cedula varchar(20),
	PRIMARY KEY (notifacacion_id),
	FOREIGN KEY (usuario_cedula) REFERENCES usuario(usuario_cedula)
);

DROP TABLE IF EXISTS propiedades_ahorro CASCADE;
CREATE TABLE propiedades_ahorro(
	propiedades_ahorro_id SERIAL,
	propiedades_ahorro_tasamax decimal,
	propiedades_ahorro_tasamin decimal,
	fondo_id bigint,
	PRIMARY KEY (propiedades_ahorro_id),
	FOREIGN KEY (fondo_id) REFERENCES fondo(fondo_id)
);

DROP TABLE IF EXISTS propiedades_credito CASCADE;
CREATE TABLE propiedades_credito(
	propiedades_credito_id SERIAL,
	propiedades_credito_tasa decimal,
	propiedades_credito_montomax decimal,
	propiedades_credito_tiempomax decimal,
	propiedades_credito_antiguedad decimal,
	propiedades_credito_administracion decimal,
	propiedades_credito_seguro decimal,
	propiedades_credito_valor_plataforma decimal,
	fondo_id bigint,
	PRIMARY KEY (propiedades_credito_id),
	FOREIGN KEY (fondo_id) REFERENCES fondo(fondo_id)
);

DROP TABLE IF EXISTS propiedades_auxilio CASCADE;
CREATE TABLE propiedades_auxilio(
	propiedades_auxilio_id SERIAL,
	propiedades_auxilio_tasa_calamidad decimal,
	propiedades_auxilio_tasa_educacion decimal,
	propiedades_auxilio_aux_max_calamidad decimal,
	propiedades_auxilio_valor_max_aux decimal,
	fondo_id bigint,
	PRIMARY KEY (propiedades_auxilio_id),
	FOREIGN KEY (fondo_id) REFERENCES fondo(fondo_id)
);

DROP TABLE IF EXISTS faq CASCADE;
CREATE TABLE faq(
	faq_referencia SERIAL,
	faq_titulo varchar(30),
	faq_descripcion varchar,
	fondo_id bigint,
	usuario_cedula varchar(20),
	PRIMARY KEY (faq_referencia),
	FOREIGN KEY (fondo_id) REFERENCES fondo(fondo_id),
	FOREIGN KEY (usuario_cedula) REFERENCES usuario(usuario_cedula)
);

DROP TABLE IF EXISTS ahorro CASCADE;
CREATE TABLE ahorro(
	ahorro_referencia SERIAL,
	ahorro_valor decimal,
	ahorro_fecha date,
	fondo_id bigint,
	usuario_cedula varchar(20),
	PRIMARY KEY (ahorro_referencia),
	FOREIGN KEY (fondo_id) REFERENCES fondo(fondo_id),
	FOREIGN KEY (usuario_cedula) REFERENCES usuario(usuario_cedula)
);

DROP TABLE IF EXISTS auxilio CASCADE;
CREATE TABLE auxilio(
	auxilio_referencia SERIAL,
	auxilio_tipo varchar,
	auxilio_valor decimal,
	auxilio_valor_aprobacion decimal,
	auxilio_fecha date,
	auxilio_estado varchar,
	fondo_id bigint,
	usuario_cedula varchar(20),
	PRIMARY KEY (auxilio_referencia),
	FOREIGN KEY (fondo_id) REFERENCES fondo(fondo_id),
	FOREIGN KEY (usuario_cedula) REFERENCES usuario(usuario_cedula)
);

DROP TABLE IF EXISTS credito CASCADE;
CREATE TABLE credito(
	credito_referencia SERIAL,
	credito_ingreso_familiar decimal,
	credito_nombre_empresa varchar,
	credito_telefono_empresa varchar,
	credito_tiempo_laborando decimal,
	credito_valor_prestamo decimal,
	credito_total_gastos decimal,
	credito_plazo_credito decimal,
	credito_numero_meses int,
	credito_valor_aprobacion decimal,
	credito_fecha date,
	credito_estado varchar,
	fondo_id bigint,
	usuario_cedula varchar(20),
	PRIMARY KEY (credito_referencia),
	FOREIGN KEY (fondo_id) REFERENCES fondo(fondo_id),
	FOREIGN KEY (usuario_cedula) REFERENCES usuario(usuario_cedula)
);
