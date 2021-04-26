CHEMIN = build/unix/crypt/release build/unix/SDPE/release build/unix/chat/server/release build/unix/chat/client/release
MKDIRP = mkdir -p
QMAKE = qmake
DIR_CRYPT = build/unix/crypt/release
DIR_SDPE = build/unix/SDPE/release
DIR_SERVEUR = build/unix/chat/server/release
DIR_CLIENT = build/unix/chat/client/release
CD = cd
AND = &&
CREER = make
ARRIERE_CRYPT = ../../../../Crypt
ARRIERE_SDPE = ../../../../SDPE
ARRIERE_SERVEUR = ../../../../../Client_Serveur
ARRIERE_CLIENT = ../../../../../App_Client
PRO_CRYPT = Crypt.pro
PRO_SDPE = SDPE.pro
PRO_SERVEUR = Client_Serveur.pro
PRO_CLIENT = App_Client.pro

all : dossiers compilation

dossiers : 
	${MKDIRP} ${CHEMIN}

compilation : QmakePro compCrypt compSDPE compServeur compClient

compCrypt : pro
	${CD} ${DIR_CRYPT} ${AND} ${CREER}

compSDPE : pro
	${CD} ${DIR_SDPE} ${AND} ${CREER}

compServeur : pro
	${CD} ${DIR_SERVEUR} ${AND} ${CREER}

compClient : pro
	${CD} ${DIR_CLIENT} ${AND} ${CREER}

QmakePro : pro

pro : crypt sdpe serveur client

crypt :
	${CD} ${DIR_CRYPT} ${AND} ${QMAKE} ${ARRIERE_CRYPT}/${PRO_CRYPT}

sdpe :
	${CD} ${DIR_SDPE} ${AND} ${QMAKE} ${ARRIERE_SDPE}/${PRO_SDPE}

serveur :
	${CD} ${DIR_SERVEUR} ${AND} ${QMAKE} ${ARRIERE_SERVEUR}/${PRO_SERVEUR}

client :
	${CD} ${DIR_CLIENT} ${AND} ${QMAKE} ${ARRIERE_CLIENT}/${PRO_CLIENT}

veryclean :
	rm -r build/