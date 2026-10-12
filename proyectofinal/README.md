# Introducción a la Ingeniería de Software

## Proyecto final: Base de datos de otro dominio

### Fecha de entrega: Por definir (semanas de certificación, del 30 de noviembre al 11 de diciembre de 2026)

Deben desarrollar en C una base de datos sobre un dominio distinto al de estudiantes. Pueden trabajar, por ejemplo, con mascotas, libros, películas, videojuegos, canciones, contactos o inventarios. El dominio deberá ser aprobado el profesor.

**Para la aprobación deberán enviar un correo la profesor con el asunto "IIS - Proyecto final". En el cuerpo del correo deberán describir de qué es su base de datos y las estructuras que tienen pensado usar.**

El proyecto retomará y adaptará el trabajo realizado en las prácticas 3 a 6. No se proporciona código inicial: deberán crear la organización, el código, las pruebas y la documentación necesarios basado en lo aprendido durante las prácticas. **Por lo que se sugiere que conforme se termine una práctica se haga el equivalente en su proyecto**.

El programa deberá:

- representar los registros mediante estructuras y definir qué campo los identifica;
- usar un conjunto sin elementos repetidos;
- permitir agregar, eliminar, buscar, reemplazar, mostrar y ordenar registros;
- usar apuntadores y memoria dinámica, incluida la liberación de la memoria reservada;
- cargar los registros desde un archivo CSV;
- validar los errores de memoria y de lectura del archivo;
- dividir el programa en módulos;
- como punto extra: incluir pruebas unitarias de las operaciones principales y de sus casos límite.

La adaptación deberá cambiar los campos, el criterio de identificación, las búsquedas, el ordenamiento, los datos del CSV y las reglas del dominio. No basta con cambiar los nombres del programa de estudiantes.

No deberán usar SQL, gestores de bases de datos, interfaces gráficas, frameworks ni tecnologías ajenas al curso.

También deberán incluir la documentación trabajada durante las prácticas: resumen del plan y registro de tiempos.

### Repositorio

Deberán seguir el **formato general de entrega** descrito en el repositorio. Antes de comenzar, actualicen su copia local:

```bash
$ cd slt-iis-20262
$ git pull upstream main
$ cd practicas/proyectofinal
```

Todo el proyecto deberá permanecer dentro de la carpeta `proyectofinal`.

### Compilación y pruebas

rear un `Makefile` que permita compilar y en caso de que hagan el punto extra, ejecutar todas las pruebas mediante:

```bash
$ make test
```

Si no hacen el punto extra basta con hacer 

```bash
$ make
```

El proyecto deberá compilar sin advertencias y todas las pruebas deberán pasar correctamente.

### Entrega

Antes de entregar, ejecuten nuevamente `make test`. Después registren y suban la versión final:

```bash
$ git add .
$ git commit -m "Entrega del proyecto final"
$ git push
```

Finalmente, deberán entregar en Classroom la liga al **commit correspondiente a la entrega**. El repositorio deberá ser privado y el usuario `manu-msr` deberá estar agregado como colaborador.
