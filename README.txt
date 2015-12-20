LE GUID (IN)COMPREHENSIF POUR COMPILER TOUT CA SUR CMAKE
By Amarre


Cmake, qu'est ce que c'est?
Cmake est un générateur de makefiles (et fichiers de projets). En gros, vous lui dites les librairies dont votre code a besoin, leur version, et où trouver les sources, et cmake travaille tout seul comme un grand pour vous générer un fichier de projet tout configuré.
Avantages : 
- Ca permet de séparer les sources de comment on les compile. Donc on a un dépôt git propre, et pas besoin de demander a git d'ignorer tout les fichiers de l'IDE.
- C'est individuel : cmake fonctionne sur tous les os, et quasiment tous les ide. Donc chacun peut bosser sur son IDE favori sans qu'on s'embête avec les problèmes de conflit.
- Ca configure automatiquement le fichier de projet : si jacky ajoute 4 nouvelles classes sur le dépot git, sans cmake quand vous allez pull votre IDE ne les connaitre pas. Il faudra les ajouter a la main dans votre projet. Avec cmake, pas besoin, il le fait tout seul.
- Ca ne se configure qu'une fois : une fois que c'est configuré, vous n'aurez plus jamais besoin d'y toucher. (et honnêtement, c'est bien plus simple à configurer que de linker vous même les librairies dans votre IDE)

Bon, on y va?

_______________________
Dépendances

Vous avez besoin des dépendances suivantes : 
- OpenCV : copiez collez mon build d'opencv, ou compilez / installez le votre. Pour ce projet vous n'avez besoin que du core d'opencv.
	Mon build : 
- Cmake : téléchargez cmake sur le site officiel. La version GUI ira bien (ou alors, vous vous débrouillerez tout seul avec la console)

Pour la suite, je suppose que vous avez mis vos dépendances dans les dossiers suivants : 
OpenCV : C:/opencv/build
Sources : C:/IN5X/Project
Build (là où le projet sera créé) : C:/IN5X/Build

Vous pouvez bien sûr mettre ça où vous voulez, du moment que vous remplacez correctement les chemins pour la suite de ce tuto.
PRECISION : il faut que les sources et le build soient adjacents! Dans le code, on accèdera aux fichiers du git par des chemins du type "../Project/mesTrucs", donc n'oubliez pas de mettre ces deux fichiers au même endroit.

_______________________
Création du projet : 

1 - Ouvrez cmake.
Vous avez 3 grandes parties dans la fenêtre de cmake.
 - En haut, 2 barres avec un bouton a leur droite (browse source, et browse build). 
 - Au centre, vous avez un grand espace blanc. C'est là que cmake vous montrera ce qu'il a configuré, et vous demandera éventuellement de remplir ce qu'il manque.
 - En bas, vous avez les logs, où cmake vous décrira ce qu'il est en train de faire. C'est là qu'il ya les deux boutons "configure" et "generate".


2 - Configuration
Allons y !

Dans browse source, il faut donner le répertoire des sources (C:/IN5X/Project chez moi)
Dans browse build, on met le répertoire du build (C:/IN5X/Build chez moi)
Au passage: Pensez à cocher "grouped" et "advanced" à droite de la barre de recherche. 

Cliquez sur "configure". Cmake ouvre une popup vous demandant de renseigner votre compilateur. Si vous utilisez mon build d'opencv, vous devez mettre VisualStudio 14 2015. Sinon, mettez le compilateur qui a servi a compiler votre build d'opencv (quand vous téléchargez les sources précompilées d'une librairie, vous aurez sûrement le choix entre pleins de versions différentes, toutes compilées avec un compilateur spécifique.)
Puis cliquez sur finish.

[LISEZ BIEN LES MESSAGES D'ERREUR DE CMAKE!] Si jamais il ya un problème il vous le dira explicitement.

Après quelques secondes de travail, cmake s'interrompt avec un message d'erreur. Lisez les logs : il vous dit qu'il n'a pas trouvé opencv dans votre variable système PATH, ni dans le PATH de cmake. Donc il vous demande de le remplir vous même. (S'il ne vous dit pas ça, vous avez déjà un problème. Googlez le, ou appelez moi)
Développez l'entrée "ungrouped entries" qui est apparue dans la partie centrale. Vous trouverez dedans une ligne "OpenCV_DIR", avec pour valeur "blablabla not found".
Cliquez sur "blabla not found", et entrez le dossier où se trouve votre build opencv. Vous pouvez le faire à la main, ou cliquer sur le bouton avec les 3 petits points tout à droite pour le choisir dans l'explorateur windows. 
Donc chez moi, j'entre : C:/opencv/build

Cliquez une nouvelle fois sur configure. Il y a moyen qu'il y ait encore du rouge la partie centrale de la fenêtre : on s'en fout. 
Dans la fenêtre de log en bas, vous devriez avoir marqué "Found opencv 3.0.0 in C:/opencv/build", puis "configuring done" sur la ligne d'après. Si vous avez ça, tout va bien. Sinon, refaites les étapes du dessus, vous avez du rater un truc. (Et si ça marche toujours pas, appelez google ou moi même à l'aide)


3 - Génération
Cliquez sur generate. C'est tout.
Si il y a un erreur à ce stade là, c'est qu'il y a problème.

Sinon, c'est fini ! Votre dossier de build devrait maintenant contenir une solution visual studio (IN5X.sln). Ouvrez la.
La solution contient 3 projets : ALL_BUILD, IN5X et ZERO_CHECK. Définissez IN5X comme projet de démarrage (clic droit sur IN5X / définir comme projet de démarrage), puis vous pouvez compiler, exécuter, et ça doit marcher.


___________________________
Utilisation

C'est pas dur, c'est toujours pareil :

Quand vous récupérez quelque chose depuis le git
1 - Récupération du projet depuis le git (git pull, tout ça)
2 - ouvrez cmake, cliquez sur configure, puis generate
3 - Rechargez votre projet visual studio

Pour pusher vers le git : rien de spécifique. Vous pouvez pusher directement.

Si vous créez des fichiers, vous devez les créer vous même. Si vous ajoutez un fichier via visual studio, il le créera dans le dossier où se trouve la solution, et ça c'est pas cool.
Donc vous devez aller vous même dans le dossier IN5X/Project, et créer les fichiers là. Puis, refaire un coup de cmake (configure/generate), et recharger votre projet, et là vous aurez vos fichiers.
Seul problème, mais ça c'est visual studio qui brise les noix : si vous avez une hiérarchie de fichiers dans vos sources, elle n'apparaîtra pas sous visual studio par défaut. Donc par exemple, si vous avez main.cpp et machin/bidule.cpp, après passage par cmake vous aurez dans visual studio bidule.cpp et main.cpp côte à côte, et le dossier machin est perdu.
Ca, j'ai fait une magouille un peu dégueu pour le régler. Donc si votre fichier est tout en bas de l'architecture (cad ya pas de sous dossiers en dessous), ça marche. Sinon, faut le rentrer à la main dans le cmake. Je ferais une explication pour ça.

Si visual studio est ouvert, vous pouvez quand même faire configure/generate depuis cmake (mais pensez à sauvegarder avant! Si vous avez des modifications non enregistrées, elles seront perdues). Visual studio vous ouvrira une popup, cliquez sur "recharger tout", et c'est bon.

___________________________
Les problèmes, les problèmes, tralalalèèèèèreu

Les problèmes les plus courants : 
 - Cmake marche pas, j'ai pas pareil que ce que tu as décris.
Lisez les messages d'erreur de cmake. Tout est dit dedans. Googlez les au pire, ou demandez moi.

 - Mon projet visual studio ne compile pas, il me dit qu'il manque des includes et ya des erreurs partout!
Probablement une erreur à la configuration de cmake. Recommencez la configuration (vous pouvez, dans cmake, faire File/Delete Cache pour repartir de zéro)
 

