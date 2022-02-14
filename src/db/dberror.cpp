/* -*- tab-width: 4 -*-
 *
 * Electric(tm) VLSI Design System
 *
 * File: dberror.c
 * Database error handler
 * Written by: Steven M. Rubin, Static Free Software
 *
 * Copyright (c) 2000 Static Free Software.
 *
 * Electric(tm) is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Electric(tm) is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Electric(tm); see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, Mass 02111-1307, USA.
 *
 * Static Free Software
 * 4119 Alpine Road
 * Portola Valley, California 94028
 * info@staticfreesoft.com
 */

#include "global.h"
#include "database.h"
#include "usr.h"

#define	NEWERRORS 1		/* uncomment to remove newly added code */

INTBIG  db_lasterror;			/* last error message */
BOOLEAN db_printerrors;			/* flag for printing internal errors */

static CHAR *db_errortype[] =
{
	N_((char*)"no error"),								/* DBNOERROR */
	N_((char*)"no memory"),							/* DBNOMEM */
	N_((char*)"bad transposition"),					/* DBBADTRANS */
	N_((char*)"bad rotation"),							/* DBBADROT */
	N_((char*)"bad prototype"),						/* DBBADPROTO */
	N_((char*)"bad parent"),							/* DBBADPARENT */
	N_((char*)"invalid instance"),						/* DBBADINST */
	N_((char*)"invalid name"),							/* DBBADNAME */
	N_((char*)"bad width"),							/* DBBADWIDTH */
	N_((char*)"bad end A node/port"),					/* DBBADENDAN */
	N_((char*)"bad end B node/port"),					/* DBBADENDBN */
	N_((char*)"bad end A connection"),					/* DBBADENDAC */
	N_((char*)"bad end B connection"),					/* DBBADENDBC */
	N_((char*)"bad end A position"),					/* DBBADENDAP */
	N_((char*)"bad end B position"),					/* DBBADENDBP */
	N_((char*)"bad new width"),						/* DBBADNEWWID */
	N_((char*)"bad cell"), 							/* DBBADCELL */
	N_((char*)"bad library"),							/* DBBADLIB */
	N_((char*)"bad size"),								/* DBBADSIZE */
	N_((char*)"bad object type"),						/* DBBADOBJECT */
	N_((char*)"bad sub port"),							/* DBBADSUBPORT */
	N_((char*)"still has arcs"),						/* DBHASARCS */
	N_((char*)"still has ports"),						/* DBHASPORTS */
	N_((char*)"cell has instances"),					/* DBHASINSTANCES */
	N_((char*)"recursive call"),						/* DBRECURSIVE */
	N_((char*)"arc not in port"),						/* DBNOTINPORT */
	N_((char*)"conflicts with primitive"),				/* DBCONFLICT */
	N_((char*)"port mismatch"),						/* DBPORTMM */
	N_((char*)"duplicate name"),						/* DBDUPLICATE */
	N_((char*)"primitive prototype"),					/* DBPRIMITIVE */
	N_((char*)"bad transformation matrix"),			/* DBBADTMAT */
	N_((char*)"variable does not exist"),				/* DBNOVAR */
	N_((char*)"variable cannot be changed"),			/* DBVARFIXED */
	N_((char*)"variable cannot be displayable array"),	/* DBVARARRDIS */
	N_((char*)"this is the last technology"),			/* DBLASTECH */
	N_((char*)"technology is still in use"),			/* DBTECINUSE */
	N_((char*)"sliding not allowed")					/* DBNOSLIDING */
};

/*
 * database error routine codes
 */
static CHAR *db_routines[] =
{
	x_((char*)"addstringtoinfstr"),	/*  1 */
	x_((char*)"addtechnology"),		/*  2 */
	x_((char*)"addtoinfstr"),			/*  3 */
	x_((char*)"allocarcinst"),			/*  4 */
	x_((char*)"allocgeom"),			/*  5 */
	x_((char*)"alloclibrary"),			/*  6 */
	x_((char*)"allocnodeinst"),		/*  7 */
	x_((char*)"allocnodeproto"),		/*  8 */
	x_((char*)"allocpolygon"),			/*  9 */
	x_((char*)"allocportarcinst"),		/* 10 */
	x_((char*)"allocportexpinst"),		/* 11 */
	x_((char*)"allocportproto"),		/* 12 */
	x_((char*)"allocstring"),			/* 13 */
	x_((char*)"alloctechnology"),		/* 14 */
	x_((char*)"allocview"),			/* 15 */
	x_((char*)"copynodeproto"),		/* 16 */
	x_((char*)"delind"),				/* 17 */
	x_((char*)"delindkey"),			/* 18 */
	x_((char*)"delvalkey"),			/* 19 */
	x_((char*)"describevariable"),		/* 20 */
	x_((char*)"extendpolygon"),		/* 21 */
	x_((char*)"initinfstr"),			/* 22 */
	x_((char*)"initobjlist"),			/* 23 */
	x_((char*)"insind"),				/* 24 */
	x_((char*)"insindkey"),			/* 25 */
	x_((char*)"killarcinst"),			/* 26 */
	x_((char*)"killlibrary"),			/* 27 */
	x_((char*)"killnodeinst"),			/* 28 */
	x_((char*)"killnodeproto"),		/* 29 */
	x_((char*)"killportproto"),		/* 30 */
	x_((char*)"killtechnology"),		/* 31 */
	x_((char*)"makekey"),				/* 32 */
	x_((char*)"modifyarcinst"),		/* 33 */
	x_((char*)"moveportproto"),		/* 34 */
	x_((char*)"newarcinst"),			/* 35 */
	x_((char*)"newlibrary"),			/* 36 */
	x_((char*)"newnodeinst"),			/* 37 */
	x_((char*)"newnodeproto"),			/* 38 */
	x_((char*)"newportproto"),			/* 39 */
	x_((char*)"newview"),				/* 40 */
	x_((char*)"replacearcinst"),		/* 41 */
	x_((char*)"replacenodeinst"),		/* 42 */
	x_((char*)"returninfstr"),			/* 43 */
	x_((char*)"setind"),				/* 44 */
	x_((char*)"setindkey"),			/* 45 */
	x_((char*)"setval"),				/* 46 */
	x_((char*)"setvalkey"),			/* 47 */
	x_((char*)"transmult"),			/* 48 */
	x_((char*)"xform"),				/* 49 */
};

/*
 * routine to report a database error
 */
INTBIG db_error(INTBIG code)
{
	db_lasterror = code;
	if (db_printerrors) telldatabaseerror();
	return(-1);
}

/*
 * routine to print an error message
 */
void telldatabaseerror(void)
{
	//REGISTER INTBIG routine, error;
	INTBIG routine, error;
	routine = (db_lasterror >> 16) - 1;
	error = db_lasterror & 0xFFFF;
	if (error == DBNOERROR)
		//ttyputmsg(_("No error"));
		ttyputmsg(_((char*)"No error"));
	else
		//ttyputmsg(x_("%s: %s"), db_routines[routine], TRANSLATE(db_errortype[error]));
		ttyputmsg(x_((char*)"%s: %s"), db_routines[routine], TRANSLATE(db_errortype[error]));
}

/******************** ERROR REPORTING ********************/

/*
 * These are the routines to log errors:
 *   initerrorlogging(CHAR *s)                   initialize for subsystem "s"
 *   e = logerror(CHAR *msg, NODEPROTO *f, k)    log message "msg" in cell "f", sort key "k"
 *   addgeomtoerror(void *e, GEOM *g, BOOLEAN s, INTBIG l, NODEINST **p)
 *                                               add geom "g" to error "e" (show if "s" nonzero)
 *   addexporttoerror(void *e, PORTPROTO *p, BOOLEAN s)  add export "pp" to error "e"
 *   addlinetoerror(void *e, x1, y1, x2, y2)     add line to error "e"
 *   addpolytoerror(void *e, POLYGON *p)         add polygon to error "e"
 *   addpointtoerror(void *e, x, y)              add point to error "e"
 *
 * To report errors, call:
 *   termerrorlogging(explain)                   complete error accumulation
 *   sorterrors()                                sort errors by key
 *   n = numerrors()                             returns number of errors
 *   s = reportnexterror(show, &g1, &g2)         report next error
 *   s = reportpreverror()                       report previous error
 *
 * To obtain errors internally, call:
 *   e = getnexterror(e, msg)                    gets error after "e" (0 is first error)
 *   msg = describeerror(e)                      return description of error "e"
 *   reporterror(e)                              reports error "e"
 *   t = getnumerrorgeom(e)                      get number of geoms on error "e"
 *   eg = geterrorgeom(e, i)                     get geom "i" on error "e"
 *   msg = describeerrorgeom(eg)                 return description of geom "eg"
 *   showerrorgeom(eg)                           highlight error geom "eg"
 *   adviseofchanges(routine)                    call "routine" when errors change
 */

typedef enum {ERRORTYPEGEOM, ERRORTYPEEXPORT, ERRORTYPELINE, ERRORTYPEPOINT} ERRORHIGHLIGHTTYPE;

#define NOERRORHIGHLIGHT ((ERRORHIGHLIGHT *)-1)

typedef struct
{
	ERRORHIGHLIGHTTYPE type;
	GEOM              *geom;
	PORTPROTO         *pp;
	BOOLEAN            showgeom;
	INTBIG             x1, y1;
	INTBIG             x2, y2;
	INTBIG             pathlen;
	NODEINST         **path;
} ERRORHIGHLIGHT;


#define NOERRORLIST ((ERRORLIST *)-1)

typedef struct iErrorList
{
	CHAR              *message;
	NODEPROTO         *cell;
	INTBIG             sortkey;
	INTBIG             index;
	INTBIG             numhighlights;
	ERRORHIGHLIGHT   **highlights;
	struct iErrorList *preverrorlist;
	struct iErrorList *nexterrorlist;
} ERRORLIST;

static ERRORLIST *db_errorlistfree = NOERRORLIST;
static ERRORLIST *db_firsterrorlist = NOERRORLIST;
static ERRORLIST *db_curerrorlist = NOERRORLIST;
static ERRORLIST *db_nexterrorlist = NOERRORLIST;
static ERRORLIST *db_preverrorlist = NOERRORLIST;

static CHAR       db_errorsystem[100] = {0};
static INTBIG     db_numerrors;
static INTBIG     db_truenumerrors;
static INTBIG     db_maxerrors = 0;
static void      *db_errorreportmutex = 0;			/* mutex for error reporting modules */
static void     (*db_errorchangedroutine)(void) = 0;

static BOOLEAN db_addtoerrorlist(ERRORLIST *el, ERRORHIGHLIGHT *eh);
static int     db_errorlistascending(const void *e1, const void *e2);
static CHAR   *db_reportcurrenterror(INTBIG showhigh, GEOM **g1, GEOM **g2);
static void    db_clearerrorlist(void);
#ifdef	NEWERRORS
static BOOLEAN db_validatecell(NODEPROTO *cell);
#endif

/*
 * Routine to free memory associated with this module.
 */
void db_freeerrormemory(void)
{
	//REGISTER ERRORLIST *el;
	ERRORLIST *el;
	/* ensure that the current error list is freed */
	db_clearerrorlist();

	/* now purge the free list */
	while (db_errorlistfree != NOERRORLIST)
	{
		el = db_errorlistfree;
		db_errorlistfree = el->nexterrorlist;
		efree((CHAR *)el);
	}
}

/*
 * Routine to free all previously stored errors and initialize the system.
 * The errors are described by "system" and up to two cells "cell1" and
 * "cell2" (may be NONODEPROTO).
 */
void initerrorlogging(CHAR *system)
{
	//REGISTER VARIABLE *var;
	VARIABLE *var;
	/* code cannot be called by multiple procesors: uses globals */
	NOT_REENTRANT;

	db_clearerrorlist();
	db_curerrorlist = NOERRORLIST;
	db_nexterrorlist = NOERRORLIST;
	db_preverrorlist = NOERRORLIST;
	estrncpy(db_errorsystem, system, 100);
	db_numerrors = db_truenumerrors = 0;
	//var = getval((INTBIG)us_tool, VTOOL, VINTEGER, x_("USER_maximum_errors"));
	var = getval((INTBIG)us_tool, VTOOL, VINTEGER, x_((char*)"USER_maximum_errors"));
	if (var == NOVARIABLE) db_maxerrors = 0; else
		db_maxerrors = var->addr;
	if (ensurevalidmutex(&db_errorreportmutex, TRUE)) return;
}

/*
 * Routine to free all previously stored errors.
 */
void db_clearerrorlist(void)
{
	//REGISTER ERRORLIST *el;
	ERRORLIST *el;
	//REGISTER ERRORHIGHLIGHT *eh;
	ERRORHIGHLIGHT *eh;
	//REGISTER INTBIG i;
	INTBIG i;
	/* code cannot be called by multiple procesors: uses globals */
	NOT_REENTRANT;

	while (db_firsterrorlist != NOERRORLIST)
	{
		/* get the next error on the list */
		el = db_firsterrorlist;
		db_firsterrorlist = el->nexterrorlist;

		/* clear memory in that module */
		efree(el->message);
		for(i=0; i<el->numhighlights; i++)
		{
			eh = el->highlights[i];
			if (eh->pathlen > 0) efree((CHAR *)eh->path);
			efree((CHAR *)eh);
		}
		if (el->numhighlights > 0) efree((CHAR *)el->highlights);

		/* place the module on the free list */
		el->nexterrorlist = db_errorlistfree;
		db_errorlistfree = el;
	}
}

/*
 * Routine to create an error message with the text "message" applying to cell "cell".
 * Returns a pointer to the message (0 on error) which can be used to add highlights.
 */
void *logerror(CHAR *message, NODEPROTO *cell, INTBIG sortkey)
{
	//REGISTER ERRORLIST *el;
	ERRORLIST *el;
	/* if too many errors, don't save it */
	db_numerrors++;
	if (db_maxerrors > 0 && db_numerrors > db_maxerrors)
	{
		if (db_numerrors == db_maxerrors+1)
			/*ttyputmsg(_("WARNING: more than %ld errors found, ignoring the rest"),
				db_maxerrors);*/
			ttyputmsg(_((char*)"WARNING: more than %ld errors found, ignoring the rest"),
				db_maxerrors);				
		return(0);
	}

	/* grab an error from the global free list (if any) */
	if (db_multiprocessing) emutexlock(db_errorreportmutex);
	el = NOERRORLIST;
	if (db_errorlistfree != NOERRORLIST)
	{
		el = db_errorlistfree;
		db_errorlistfree = el->nexterrorlist;
	}
	if (db_multiprocessing) emutexunlock(db_errorreportmutex);

	/* if nothing on the list, allocate one */
	if (el == NOERRORLIST)
	{
		el = (ERRORLIST *)emalloc(sizeof (ERRORLIST), db_cluster);
		if (el == 0) return(0);
	}

	/* store information about the error */
	if (allocstring(&el->message, message, db_cluster)) return(0);
	el->cell = cell;
	el->sortkey = sortkey;
	el->numhighlights = 0;

	/* link the error into the global list */
	if (db_multiprocessing) emutexlock(db_errorreportmutex);
	el->preverrorlist = NOERRORLIST;
	el->nexterrorlist = db_firsterrorlist;
	if (db_firsterrorlist != NOERRORLIST) db_firsterrorlist->preverrorlist = el;
	db_firsterrorlist = el;
	if (db_multiprocessing) emutexunlock(db_errorreportmutex);

	db_truenumerrors++;
	return((void *)el);
}

/*
 * Routine to add "geom" to the error in "errorlist".  Also adds a
 * hierarchical traversal path "path" (which is "pathlen" long).
 */
void addgeomtoerror(void *errorlist, GEOM *geom, BOOLEAN showit, INTBIG pathlen, NODEINST **path)
{
	//REGISTER ERRORLIST *el;
	ERRORLIST *el;
	//REGISTER ERRORHIGHLIGHT *eh;
	ERRORHIGHLIGHT *eh;
	//REGISTER INTBIG i;
	INTBIG i;
	if (errorlist == 0) return;
	el = (ERRORLIST *)errorlist;
	eh = (ERRORHIGHLIGHT *)emalloc(sizeof (ERRORHIGHLIGHT), db_cluster);
	if (eh == 0) return;
	eh->type = ERRORTYPEGEOM;
	eh->geom = geom;
	eh->showgeom = showit;
	eh->pathlen = pathlen;
	if (pathlen > 0)
	{
		eh->path = (NODEINST **)emalloc(pathlen * (sizeof (NODEINST *)), db_cluster);
		if (eh->path == 0) return;
		for(i=0; i<pathlen; i++)
			eh->path[i] = path[i];
	}
	(void)db_addtoerrorlist(el, eh);
}

/*
 * Routine to add "pp" to the error in "errorlist".
 */
void addexporttoerror(void *errorlist, PORTPROTO *pp, BOOLEAN showit)
{
	//REGISTER ERRORLIST *el;
	ERRORLIST *el;
	//REGISTER ERRORHIGHLIGHT *eh;
	ERRORHIGHLIGHT *eh;
	if (errorlist == 0) return;
	el = (ERRORLIST *)errorlist;
	eh = (ERRORHIGHLIGHT *)emalloc(sizeof (ERRORHIGHLIGHT), db_cluster);
	if (eh == 0) return;
	eh->type = ERRORTYPEEXPORT;
	eh->pp = pp;
	eh->showgeom = showit;
	eh->pathlen = 0;
	(void)db_addtoerrorlist(el, eh);	
}

/*
 * Routine to add line (x1,y1)=>(x2,y2) to the error in "errorlist".
 */
void addlinetoerror(void *errorlist, INTBIG x1, INTBIG y1, INTBIG x2, INTBIG y2)
{
	//REGISTER ERRORLIST *el;
	ERRORLIST *el;
	//REGISTER ERRORHIGHLIGHT *eh;
	ERRORHIGHLIGHT *eh;
	if (errorlist == 0) return;
	el = (ERRORLIST *)errorlist;
	eh = (ERRORHIGHLIGHT *)emalloc(sizeof (ERRORHIGHLIGHT), db_cluster);
	if (eh == 0) return;
	eh->type = ERRORTYPELINE;
	eh->x1 = x1;
	eh->y1 = y1;
	eh->x2 = x2;
	eh->y2 = y2;
	eh->pathlen = 0;
	(void)db_addtoerrorlist(el, eh);	
}

/*
 * Routine to add polygon "poly" to the error in "errorlist".
 */
void addpolytoerror(void *errorlist, POLYGON *poly)
{
	//REGISTER INTBIG i, prev;
	INTBIG i, prev;
	INTBIG lx, hx, ly, hy;

	if (errorlist == 0) return;
	if (isbox(poly, &lx, &hx, &ly, &hy))
	{
		(void)addlinetoerror(errorlist, lx, ly, lx, hy);
		(void)addlinetoerror(errorlist, lx, hy, hx, hy);
		(void)addlinetoerror(errorlist, hx, hy, hx, ly) ;
		(void)addlinetoerror(errorlist, hx, ly, lx, ly);;
	} else
	{
		for(i=0; i<poly->count; i++)
		{
			if (i == 0) prev = poly->count-1; else prev = i-1;
			(void)addlinetoerror(errorlist, poly->xv[prev], poly->yv[prev],
				poly->xv[i], poly->yv[i]);
		}
	}
}

/*
 * Routine to add point (x,y) to the error in "errorlist".
 */
void addpointtoerror(void *errorlist, INTBIG x, INTBIG y)
{
	//REGISTER ERRORLIST *el;
	ERRORLIST *el;
	//REGISTER ERRORHIGHLIGHT *eh;
	ERRORHIGHLIGHT *eh;
	if (errorlist == 0) return;
	el = (ERRORLIST *)errorlist;
	eh = (ERRORHIGHLIGHT *)emalloc(sizeof (ERRORHIGHLIGHT), db_cluster);
	if (eh == 0) return;
	eh->type = ERRORTYPEPOINT;
	eh->x1 = x;
	eh->y1 = y;
	eh->pathlen = 0;
	(void)db_addtoerrorlist(el, eh);	
}

/*
 * Routine called when all errors are logged.  Initializes pointers for replay of errors.
 */
void termerrorlogging(BOOLEAN explain)
{
	//REGISTER INTBIG errs;
	INTBIG errs;
	//REGISTER ERRORLIST *el;
	ERRORLIST *el;
	/* code cannot be called by multiple procesors: uses globals */
	NOT_REENTRANT;

	db_curerrorlist = NOERRORLIST;
	db_nexterrorlist = db_firsterrorlist;
	db_preverrorlist = NOERRORLIST;

	/* enumerate the errors */
	errs = 0;
	for(el = db_firsterrorlist; el != NOERRORLIST; el = el->nexterrorlist)
		el->index = ++errs;

	if (db_errorchangedroutine != 0)
		(*db_errorchangedroutine)();

	if (errs > 0 && explain)
	{
		/*ttyputmsg(_("To review errors, type:"));
		ttyputmsg(_(" >  Show the next error"));
		ttyputmsg(_(" <  Show the previous error"));*/
		ttyputmsg(_((char*)"To review errors, type:"));
		ttyputmsg(_((char*)" >  Show the next error"));
		ttyputmsg(_((char*)" <  Show the previous error"));		
	}
}

/*
 * Routine to sort the errors by their "key" (a value provided to "logerror()").
 * Obviously, this should be called after all errors have been reported.
 */
void sorterrors(void)
{
	//REGISTER ERRORLIST *el, **sortedlist;
	ERRORLIST *el, **sortedlist;
	//REGISTER INTBIG i;
	INTBIG i;
	if (db_truenumerrors == 0) return;

	/* code cannot be called by multiple procesors: uses globals */
	NOT_REENTRANT;

	sortedlist = (ERRORLIST **)emalloc(db_truenumerrors * (sizeof (ERRORLIST *)), db_cluster);
	if (sortedlist == 0) return;
	i = 0;
	for(el = db_firsterrorlist; el != NOERRORLIST; el = el->nexterrorlist)
		sortedlist[i++] = el;
	esort(sortedlist, db_truenumerrors, sizeof (ERRORLIST *), db_errorlistascending);
	for(i=0; i<db_truenumerrors; i++)
	{
		el = sortedlist[i];
		el->index = i+1;
		if (i == 0) el->preverrorlist = NOERRORLIST; else
			el->preverrorlist = sortedlist[i-1];
		if (i < db_truenumerrors-1) el->nexterrorlist = sortedlist[i+1]; else
			el->nexterrorlist = NOERRORLIST;
	}
	db_firsterrorlist = sortedlist[0];
	efree((CHAR *)sortedlist);
}

/*
 * Routine to return the number of logged errors.
 */
INTBIG numerrors(void)
{
	return(db_numerrors);
}

/*
 * Routine to advance to the next error and report it.
 */
CHAR *reportnexterror(INTBIG showhigh, GEOM **g1, GEOM **g2)
{
	if (db_nexterrorlist != NOERRORLIST)
	{
		db_curerrorlist = db_nexterrorlist;
		db_nexterrorlist = db_curerrorlist->nexterrorlist;
		db_preverrorlist = db_curerrorlist->preverrorlist;
	} else
	{
		/* at end: go to start of list */
		db_curerrorlist = db_firsterrorlist;
		if (db_curerrorlist == NOERRORLIST) db_nexterrorlist = NOERRORLIST; else
			db_nexterrorlist = db_curerrorlist->nexterrorlist;
		db_preverrorlist = NOERRORLIST;
	}
	return(db_reportcurrenterror(showhigh, g1, g2));
}

/*
 * Routine to back up to the previous error and report it.
 */
CHAR *reportpreverror(void)
{
	//REGISTER ERRORLIST *el;
	ERRORLIST *el;
	if (db_preverrorlist != NOERRORLIST)
	{
		db_curerrorlist = db_preverrorlist;
		db_nexterrorlist = db_curerrorlist->nexterrorlist;
		db_preverrorlist = db_curerrorlist->preverrorlist;
	} else
	{
		/* at start: go to end of list */
		db_preverrorlist = db_curerrorlist = db_nexterrorlist = NOERRORLIST;
		for(el = db_firsterrorlist; el != NOERRORLIST; el = el->nexterrorlist)
		{
			db_preverrorlist = db_curerrorlist;
			db_curerrorlist = el;
		}
	}
	return(db_reportcurrenterror(1, 0, 0));
}

/*
 * Routine to return a list of errors.  On the first call, set "e" to zero.
 * Returns the next in the list (zero when done).
 */
void *getnexterror(void *elv)
{
	//REGISTER ERRORLIST *el;
	ERRORLIST *el;
	if (elv == 0) el = db_firsterrorlist; else
	{
		el = (ERRORLIST *)elv;
		if (el == NOERRORLIST) return(0);
		el = el->nexterrorlist;
	}
	if (el == NOERRORLIST) return(0);
	return((void *)el);
}

/*
 * Routine to return the number of objects associated with error "e".  Only
 * returns "geom" objects
 */
INTBIG getnumerrorgeom(void *elv)
{
	//REGISTER ERRORLIST *el;
	ERRORLIST *el;
	//REGISTER ERRORHIGHLIGHT *eh;
	ERRORHIGHLIGHT *eh;
	//REGISTER INTBIG i, total;
	INTBIG i, total;
	if (elv == 0) return(0);
	el = (ERRORLIST *)elv;
	total = 0;
	for(i=0; i<el->numhighlights; i++)
	{
		eh = el->highlights[i];
		if (eh->type == ERRORTYPEGEOM) total++;
	}
	return(total);
}

/*
 * Routine to return the next object in a list of objects on an error.  The previous
 * object is "eg".  Returns zero at the end of the list.
 */
void *geterrorgeom(void *elv, INTBIG index)
{
	//REGISTER ERRORLIST *el;
	ERRORLIST *el;
	//REGISTER ERRORHIGHLIGHT *eh;
	ERRORHIGHLIGHT *eh;
	//REGISTER INTBIG i, total;
	INTBIG i, total;
	if (elv == 0) return(0);
	el = (ERRORLIST *)elv;
	total = 0;
	for(i=0; i<el->numhighlights; i++)
	{
		eh = el->highlights[i];
		if (eh->type != ERRORTYPEGEOM) continue;
		if (total == index) break;
		total++;
	}
	if (i >= el->numhighlights) return(0);
	return(eh);
}

/*
 * Routine to describe an object on an error.  The object is "ehv".
 */
CHAR *describeerrorgeom(void *ehv)
{
	//REGISTER ERRORHIGHLIGHT *eh;
	ERRORHIGHLIGHT *eh;
	//REGISTER GEOM *geom;
	GEOM *geom;
	//REGISTER void *infstr;
	void *infstr;
	//REGISTER INTBIG i;
	INTBIG i;
	//REGISTER NODEINST *ni;
	NODEINST *ni;
	//if (ehv == 0) return(x_(""));
	if (ehv == 0) return(x_((char*)""));
	eh = (ERRORHIGHLIGHT *)ehv;
	geom = eh->geom;
	infstr = initinfstr();
	if (geom->entryisnode)
		//formatinfstr(infstr, _("Node %s"), describenodeinst(geom->entryaddr.ni));
		formatinfstr(infstr, _((char*)"Node %s"), describenodeinst(geom->entryaddr.ni));
	else
		//formatinfstr(infstr, _("Arc %s"), describearcinst(geom->entryaddr.ai));
		formatinfstr(infstr, _((char*)"Arc %s"), describearcinst(geom->entryaddr.ai));
	for(i=0; i<eh->pathlen; i++)
	{
		ni = eh->path[i];
		/*formatinfstr(infstr, _(" in %s:%s:%s"), ni->parent->lib->libname,
			nldescribenodeproto(ni->parent), describenodeinst(ni));*/
		formatinfstr(infstr, _((char*)" in %s:%s:%s"), ni->parent->lib->libname,
			nldescribenodeproto(ni->parent), describenodeinst(ni));			
	}
	return(returninfstr(infstr));
}

/*
 * Routine to highlight an object on an error.  The object is "ehv".
 */
void showerrorgeom(void *ehv)
{
	//REGISTER ERRORHIGHLIGHT *eh;
	ERRORHIGHLIGHT *eh;
	//REGISTER GEOM *geom;
	GEOM *geom;
	INTBIG lx, hx, ly, hy;
	//REGISTER INTBIG i;
	INTBIG i;
	//REGISTER WINDOWPART *w;
	WINDOWPART *w;
	//REGISTER NODEPROTO *np;
	NODEPROTO *np;
	if (ehv == 0) return;
	eh = (ERRORHIGHLIGHT *)ehv;
	geom = eh->geom;
	np = geomparent(geom);
	for(w = el_topwindowpart; w != NOWINDOWPART; w = w->nextwindowpart)
		if (w->curnodeproto == np) break;
	if (w == NOWINDOWPART)
	{
		el_curwindowpart = us_wantnewwindow(0);
		us_fullview(np, &lx, &hx, &ly, &hy);
		us_switchtocell(np, lx, hx, ly, hy, NONODEINST, NOPORTPROTO, FALSE, FALSE, FALSE);
	}
	//(void)asktool(us_tool, x_("show-object"), (INTBIG)geom);
	(void)asktool(us_tool, x_((char*)"show-object"), (INTBIG)geom);
	for(i=eh->pathlen-1; i>=0; i--)
	{
		sethierarchicalparent(np, eh->path[i], NOWINDOWPART, 0, 0);
		np = eh->path[i]->parent;
	}
}

/*
 * Routine to describe error "elv".
 */
CHAR *describeerror(void *elv)
{
	//REGISTER ERRORLIST *el;
	ERRORLIST *el;
	//if (elv == 0) return(x_(""));
	if (elv == 0) return(x_((char*)""));
	el = (ERRORLIST *)elv;
	return(el->message);
}

/*
 * Routine to highlight and report error "elv".
 */
void reporterror(void *elv)
{
	//REGISTER ERRORLIST *el;
	ERRORLIST *el;
	if (elv == 0) return;
	el = (ERRORLIST *)elv;
	db_curerrorlist = el;
	db_nexterrorlist = db_curerrorlist->nexterrorlist;
	db_preverrorlist = db_curerrorlist->preverrorlist;
	(void)db_reportcurrenterror(1, 0, 0);
}

/*
 * Routine to request that "routine" be called whenever any changes are made to the list of
 * errors.
 */
void adviseofchanges(void (*routine)(void))
{
	db_errorchangedroutine = routine;
}

/******************** ERROR REPORTING SUPPORT ROUTINES ********************/

/*
 * Internal routine to add detail to an error.  The error is "el" and the detail is "eh".
 * Returns TRUE on error.
 */
BOOLEAN db_addtoerrorlist(ERRORLIST *el, ERRORHIGHLIGHT *eh)
{
	//REGISTER ERRORHIGHLIGHT **neweh;
	ERRORHIGHLIGHT **neweh;
	//REGISTER INTBIG i;
	INTBIG i;
	neweh = (ERRORHIGHLIGHT **)emalloc((sizeof (ERRORHIGHLIGHT *)) * (el->numhighlights+1),
		db_cluster);
	if (neweh == 0) return(TRUE);
	for(i=0; i<el->numhighlights; i++)
		neweh[i] = el->highlights[i];
	neweh[el->numhighlights] = eh;
	if (el->numhighlights > 0) efree((CHAR *)el->highlights);
	el->highlights = neweh;
	el->numhighlights++;
	return(FALSE);
}

/*
 * Helper routine for "sorterrors()" to sort errors by their key
 */
int db_errorlistascending(const void *e1, const void *e2)
{
	//REGISTER ERRORLIST *el1, *el2;
	ERRORLIST *el1, *el2;
	el1 = *((ERRORLIST **)e1);
	el2 = *((ERRORLIST **)e2);
	return(el1->sortkey - el2->sortkey);
}

/*
 * Routine to return the error message associated with the current error.
 * Highlights associated graphics if "showhigh" is nonzero.  Fills "g1" and "g2"
 * with associated geometry modules (if nonzero).
 */
#define MAXCELLS 20

CHAR *db_reportcurrenterror(INTBIG showhigh, GEOM **g1, GEOM **g2)
{
	//REGISTER ERRORLIST *el;
	ERRORLIST *el;
	//REGISTER NODEPROTO *cell;
	NODEPROTO *cell;
	//REGISTER PORTPROTO *pp;
	PORTPROTO *pp;
	NODEPROTO *celllist[MAXCELLS];
	//REGISTER INTBIG i, j, consize, numcells, havegeoms, newwindows, count, hierpathcount;
	INTBIG i, j, consize, numcells, havegeoms, newwindows, count, hierpathcount;
	//REGISTER NODEINST **hierpath, *ni;
	NODEINST **hierpath, *ni;
	//REGISTER ARCINST *ai;
	ARCINST *ai;
	INTBIG lx, hx, ly, hy;
	//REGISTER ERRORHIGHLIGHT *eh;
	ERRORHIGHLIGHT *eh;
	//REGISTER GEOM *geom1, *geom2;
	GEOM *geom1, *geom2;
	//REGISTER WINDOWPART *w;
	WINDOWPART *w;
	WINDOWPART *neww[4];
	//REGISTER void *infstr;
	void *infstr;
	el = db_curerrorlist;
	if (el == NOERRORLIST)
	{
		infstr = initinfstr();
		//formatinfstr(infstr, _("No %s errors"), db_errorsystem);
		formatinfstr(infstr, _((char*)"No %s errors"), db_errorsystem);
		return(returninfstr(infstr));
	}

	/* turn off highlighting */
	if (showhigh != 0)
	{
		//(void)asktool(us_tool, x_("clear"));
		(void)asktool(us_tool, x_((char*)"clear"));
		/* validate the cell (it may have been deleted) */
		cell = el->cell;
#ifdef	NEWERRORS
		if (cell != NONODEPROTO)
		{
			if (!db_validatecell(cell))
			{
				infstr = initinfstr();
				/*formatinfstr(infstr, _("%s error %ld of %ld (but cell is deleted): %s"), db_errorsystem,
					el->index, db_numerrors, el->message);*/
				formatinfstr(infstr, _((char*)"%s error %ld of %ld (but cell is deleted): %s"), db_errorsystem,
					el->index, db_numerrors, el->message);					
				return(returninfstr(infstr));
			}
		}
#else
		{
			REGISTER NODEPROTO *np;
			REGISTER LIBRARY *lib;
			for(lib = el_curlib; lib != NOLIBRARY; lib = lib->nextlibrary)
			{
				for(np = lib->firstnodeproto; np != NONODEPROTO; np = np->nextnodeproto)
					if (np == cell) break;
				if (np != NONODEPROTO) break;
			}
			if (lib == NOLIBRARY)
			{
				infstr = initinfstr();
				formatinfstr(infstr, _("%s error %ld of %ld (but cell is deleted): %s"), db_errorsystem,
					el->index, db_numerrors, el->message);
				return(returninfstr(infstr));
			}
		}
#endif

		/* first figure out which cells need to be displayed */
		numcells = 0;
		for(i=0; i<el->numhighlights; i++)
		{
			eh = el->highlights[i];
			hierpathcount = 0;
			cell = el->cell;
#ifdef	NEWERRORS
			if (eh->showgeom && eh->type == ERRORTYPEGEOM && cell == NONODEPROTO)
			{
				cell = geomparent(eh->geom);
				if (cell != NONODEPROTO && !db_validatecell(cell))
					cell = NONODEPROTO;
			}
#endif
			switch (eh->type)
			{
				case ERRORTYPEGEOM:
					if (!eh->showgeom) cell = NONODEPROTO; else
#ifdef	NEWERRORS
						if (cell != NONODEPROTO)
#endif
					{
						/* validate the geometry */
						for(ai = cell->firstarcinst; ai != NOARCINST; ai = ai->nextarcinst)
							if (ai->geom == eh->geom) break;
						if (ai == NOARCINST)
						{
							for(ni = cell->firstnodeinst; ni != NONODEINST; ni = ni->nextnodeinst)
								if (ni->geom == eh->geom) break;
							if (ni == NONODEINST)
							{
								/* geometry pointer is not valid */
								eh->showgeom = FALSE;
								cell = NONODEPROTO;
							}
						}
					}
					if (eh->showgeom)
					{
						cell = geomparent(eh->geom);
						if (eh->pathlen > 0)
						{
							hierpathcount = eh->pathlen;
							hierpath = eh->path;
						}
					}
					break;
				case ERRORTYPEEXPORT:
					if (!eh->showgeom) cell = NONODEPROTO; else
#ifdef	NEWERRORS
						if (cell != NONODEPROTO)
#endif
					{
						/* validate the export */
						for(pp = cell->firstportproto; pp != NOPORTPROTO; pp = pp->nextportproto)
							if (pp == eh->pp) break;
						if (pp == NOPORTPROTO)
						{
							eh->showgeom = FALSE;
							cell = NONODEPROTO;
						} else cell = eh->pp->parent;
					}
					break;
				case ERRORTYPELINE:
				case ERRORTYPEPOINT:
					break;
			}
			if (cell == NONODEPROTO) continue;
			for(j=0; j<numcells; j++)
				if (celllist[j] == cell) break;
			if (j < numcells) continue;
			if (numcells >= MAXCELLS) break;
			celllist[numcells] = cell;
			numcells++;
		}

		/* be sure that all requested cells are shown */
		newwindows = 0;
		for(i=0; i<numcells; i++)
		{
			/* see if the cell is already being displayed */
			for(w = el_topwindowpart; w != NOWINDOWPART; w = w->nextwindowpart)
				if (w->curnodeproto == celllist[i]) break;
			if (w != NOWINDOWPART)
			{
				/* already displayed: mark this cell done */
				bringwindowtofront(w->frame);
				celllist[i] = NONODEPROTO;
				continue;
			}

			/* keep a count of the number of new windows needed */
			newwindows++;
		}
		while (newwindows > 0)
		{
			neww[0] = us_wantnewwindow(0);
			newwindows--;
			if (newwindows > 0)
			{
				el_curwindowpart = neww[0];
				neww[1] = us_splitcurrentwindow(2, FALSE, &neww[0], 50);
				newwindows--;
			}
			if (newwindows > 0)
			{
				el_curwindowpart = neww[0];
				neww[2] = us_splitcurrentwindow(1, FALSE, &neww[0], 50);
				newwindows--;
			}
			if (newwindows > 0)
			{
				el_curwindowpart = neww[1];
				neww[3] = us_splitcurrentwindow(1, FALSE, &neww[1], 50);
				newwindows--;
			}
			count = 0;
			for(i=0; i<numcells; i++)
			{
				if (celllist[i] == NONODEPROTO) continue;
				el_curwindowpart = neww[count++];
				us_fullview(celllist[i], &lx, &hx, &ly, &hy);
				us_switchtocell(celllist[i], lx, hx, ly, hy, NONODEINST, NOPORTPROTO, FALSE, FALSE, FALSE);
				celllist[i] = NONODEPROTO;
				if (count >= 4) break;
			}
		}
	}

	/* first show the geometry associated with this error */
	geom1 = geom2 = NOGEOM;
	havegeoms = 0;
	for(i=0; i<el->numhighlights; i++)
	{
		eh = el->highlights[i];
		if (showhigh == 0 || !eh->showgeom) continue;
		switch (eh->type)
		{
			case ERRORTYPEGEOM:
				if (geom1 == NOGEOM) geom1 = eh->geom; else
					if (geom2 == NOGEOM) geom2 = eh->geom;

				/* include this geometry module in list to show */
				if (havegeoms == 0) infstr = initinfstr(); else
					addtoinfstr(infstr, '\n');
				havegeoms++;
				/*formatinfstr(infstr, x_("CELL=%s FROM=0%lo;-1;0"),
					describenodeproto(geomparent(eh->geom)), (INTBIG)eh->geom);*/
				formatinfstr(infstr, x_((char*)"CELL=%s FROM=0%lo;-1;0"),
					describenodeproto(geomparent(eh->geom)), (INTBIG)eh->geom);					
				break;
			case ERRORTYPEEXPORT:
				if (havegeoms == 0) infstr = initinfstr(); else
					addtoinfstr(infstr, '\n');
				havegeoms++;
				/*formatinfstr(infstr, x_("CELL=%s TEXT=0%lo;0%lo;-"),
					describenodeproto(eh->pp->parent), (INTBIG)eh->pp->subnodeinst->geom,
						(INTBIG)eh->pp);*/
				formatinfstr(infstr, x_((char*)"CELL=%s TEXT=0%lo;0%lo;-"),
					describenodeproto(eh->pp->parent), (INTBIG)eh->pp->subnodeinst->geom,
						(INTBIG)eh->pp);						
				break;
			case ERRORTYPELINE:
			case ERRORTYPEPOINT:
				break;
		}

		/* set the hierarchical path */
		if (eh->type == ERRORTYPEGEOM && eh->showgeom && eh->pathlen > 0)
		{
			cell = geomparent(eh->geom);
			for(w=el_topwindowpart; w != NOWINDOWPART; w = w->nextwindowpart)
				if (w->curnodeproto == cell) break;
			if (w != NOWINDOWPART)
			{
				for(j=eh->pathlen-1; j>=0; j--)
				{
					sethierarchicalparent(cell, eh->path[j], w, 0, 0);
					cell = eh->path[j]->parent;
				}
			}
		}
	}

	if (havegeoms != 0)
		//(void)asktool(us_tool, x_("show-multiple"), (INTBIG)returninfstr(infstr));
		(void)asktool(us_tool, x_((char*)"show-multiple"), (INTBIG)returninfstr(infstr));
	/* now show the lines and points associated with this error */
	for(i=0; i<el->numhighlights; i++)
	{
		eh = el->highlights[i];
		switch (eh->type)
		{
			case ERRORTYPELINE:
				if (showhigh != 0)
					/*(void)asktool(us_tool, x_("show-line"), eh->x1, eh->y1, eh->x2, eh->y2,
						el->cell);*/
					(void)asktool(us_tool, x_((char*)"show-line"), eh->x1, eh->y1, eh->x2, eh->y2,
						el->cell);						
				break;
			case ERRORTYPEPOINT:
				if (showhigh != 0)
				{
					consize = lambdaofcell(el->cell) * 5;
					/*(void)asktool(us_tool, x_("show-line"), eh->x1-consize, eh->y1-consize,
						eh->x1+consize, eh->y1+consize, el->cell);
					(void)asktool(us_tool, x_("show-line"), eh->x1-consize, eh->y1+consize,
						eh->x1+consize, eh->y1-consize, el->cell);*/
					(void)asktool(us_tool, x_((char*)"show-line"), eh->x1-consize, eh->y1-consize,
						eh->x1+consize, eh->y1+consize, el->cell);
					(void)asktool(us_tool, x_((char*)"show-line"), eh->x1-consize, eh->y1+consize,
						eh->x1+consize, eh->y1-consize, el->cell);						
				}
				break;
			case ERRORTYPEGEOM:
			case ERRORTYPEEXPORT:
				break;
		}
	}

	/* return geometry if requested */
	if (g1 != 0) *g1 = geom1;
	if (g2 != 0) *g2 = geom2;

	/* return the error message */
	infstr = initinfstr();
	/*formatinfstr(infstr, _("%s error %ld of %ld: %s"), db_errorsystem,
		el->index, db_numerrors, el->message);*/
	formatinfstr(infstr, _((char*)"%s error %ld of %ld: %s"), db_errorsystem,
		el->index, db_numerrors, el->message);		
	return(returninfstr(infstr));
}

#ifdef NEWERRORS
BOOLEAN db_validatecell(NODEPROTO *cell)
{
	//REGISTER LIBRARY *lib;
	LIBRARY *lib;
	//REGISTER NODEPROTO *np;
	NODEPROTO *np;
	for(lib = el_curlib; lib != NOLIBRARY; lib = lib->nextlibrary)
	{
		for(np = lib->firstnodeproto; np != NONODEPROTO; np = np->nextnodeproto)
			if (np == cell) return(TRUE);
	}
	return(FALSE);
}
#endif
