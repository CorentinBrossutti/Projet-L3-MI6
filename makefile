CHEMIN_BUILD = build/unix/crypt/release build/unix/SDPE/release build/unix/chat/server/release build/unix/chat/client/release
CHEMIN_DEPLOY = deploy/mpir deploy/crypt/release
MKDIRP = mkdir -p
CPR = cp -r
MV = mv
QMAKE = qmake
DIR_CRYPT = build/unix/crypt/release
DIR_SDPE = build/unix/SDPE/release
DIR_SERVEUR = build/unix/chat/server/release
DIR_CLIENT = build/unix/chat/client/release
DIR_MPIR_RELEASE = lib/unix/mpir/release
DIR_DEPLOY = deploy
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
EXEC_SDPE = MI6.SDPE
EXEC_SERVEUR = MI6.ChatServer
EXEC_CLIENT = MI6.ChatClient

all : dossiers deploy

dossiers : 
	${MKDIRP} ${CHEMIN_BUILD} ${AND} ${MKDIRP} ${CHEMIN_DEPLOY}

deploy : compilation copyMpir mvCrypt mvSDPE mvClient mvServeur nettoyer

copyMpir :
	${CPR} ${DIR_MPIR_RELEASE} ${DIR_DEPLOY}/mpir

mvCrypt :
	${MV} ${DIR_CRYPT}/lib* ${DIR_DEPLOY}/crypt/release

mvSDPE :
	${MV} ${DIR_SDPE}/${EXEC_SDPE} ${DIR_DEPLOY}

mvClient :
	${MV} ${DIR_CLIENT}/${EXEC_CLIENT} ${DIR_DEPLOY}

mvServeur :
	${MV} ${DIR_SERVEUR}/${EXEC_SERVEUR} ${DIR_DEPLOY}

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

nettoyer :
	rm -r build/

clean :
	rm -r deploy/