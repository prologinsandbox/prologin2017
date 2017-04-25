======
Manuel
======

------
Établi
------

Chaque établi peut être représenté par une grille carrée de 6 cases de côté.
Chaque apprenti a son propre établi.

Élément
=======

Les éléments sont les matières premières mis à votre disposition. Il y
en a cinq :

* Le *plomb*, le *fer* et le *cuivre* sont les trois métaux que vous pouvez
  transmuter en or. Les trois ont le même rendement, mais ne peuvent
  pas être mélangés.

.. raw:: latex

   \begin{figure}[!h]
     \centering
     \captionsetup[subfigure]{labelformat=empty}
     \begin{subfigure}[b]{2cm}
       \includegraphics[width=\textwidth]{img/material-lead}
       \caption{Plomb}
     \end{subfigure}
     \begin{subfigure}[b]{2cm}
       \includegraphics[width=\textwidth]{img/material-iron}
       \caption{Fer}
     \end{subfigure}
     \begin{subfigure}[b]{2cm}
       \includegraphics[width=\textwidth]{img/material-copper}
       \caption{Cuivre}
     \end{subfigure}
   \end{figure}

* Le *mercure* et le *soufre* sont les deux éléments volatiles qui permettront
  de catalyser un élément vers un autre élément.

.. raw:: latex

   \begin{figure}[!h]
     \centering
     \captionsetup[subfigure]{labelformat=empty}
     \begin{subfigure}[b]{2cm}
       \includegraphics[width=\textwidth]{img/material-mercury}
       \caption{Mercure}
     \end{subfigure}
     \begin{subfigure}[b]{2cm}
       \includegraphics[width=\textwidth]{img/material-sulfur}
       \caption{Soufre}
     \end{subfigure}
   \end{figure}

Échantillon
===========

Un échantillon est une paire d'éléments. Ils peuvent être composés de deux
éléments identiques ou distincts.


---------------------
Déroulement d'un tour
---------------------

Au début de votre tour, vous recevrez l'échantillon créé par votre
adversaire pour vous au tour précédent. Vous pouvez réaliser les actions
ci-dessous dans n'importe quel ordre.

Actions
=======

Donner un échantillon
---------------------

Pour inculper la solidarité et exacerber l'entraîde entre ses apprentis, il est
demandé à tous les apprentis de se rendre service et de ne jamais se servir
soit-même dans la réserve.

À chaque tour N, les deux apprentis créent un échantillon pour leur adversaire,
échantillon qui sera posé au tour N+1. Si vous oubliez de créer cet
échantillon, votre adversaire recevra un échantillon identique à celui qu'il a
lui-même créé au tour précédent.
Par souci d'égalité, chaque échantillon doit avoir au minimum *un élément en
commun* avec l'échantillon reçu au tour précédent. Par exemple, si l'apprenti A
confie un échantillon de plomb et de mercure à l'apprenti B, l'apprenti B devra
lui rendre un échantillon contenant un élément de son choix, et soit du
mercure, soit du plomb.

Poser un échantillon
--------------------

Une fois l'échantillon en main, vous devez délicatement le déposer sur votre
établi.

* Un élément au moins de l'échantillon doit être posé à un emplacement adjacent
  à un élément de même type.
* Si il n'y a aucun élément identique entre l'échantillon et ce qui est déjà
  posé sur l'établi, l'échantillon peut être posé n'importe où.
* Si il n'y a pas d'emplacement valide, vous serez obligés de transmuter une
  zone pour libérer de la place sur l'établi, et il ne vous reste plus qu'à
  assassiner discrètement votre compère qui - n'en doutez pas ! - savait
  pertinemment quel tour il était en train de vous jouer.

Transmuter
----------

Lorsque vous possédez une zone d'un certain métal (cuivre, fer ou plomb), vous
pouvez lancer la *transmutation* en or. Plus cette zone est grande, plus vous
obtiendrez d'or.

.. raw:: latex

   \begin{figure}[!h]
     \centering
     \captionsetup[subfigure]{labelformat=empty}
     \begin{subfigure}[b]{2cm}
       \includegraphics[width=\textwidth]{img/material-lead}
       \caption{Plomb}
     \end{subfigure}
     \begin{subfigure}[b]{2cm}
       \includegraphics[width=\textwidth]{img/material-iron}
       \caption{Fer}
     \end{subfigure}
     \begin{subfigure}[b]{2cm}
       \includegraphics[width=\textwidth]{img/material-copper}
       \caption{Cuivre}
     \end{subfigure}
     \begin{subfigure}[b]{2cm}
       $\xrightarrow{\text{transmutation}}$
       \caption{\newline} % latex hacks are teh shit
     \end{subfigure}
     \begin{subfigure}[b]{2cm}
       \includegraphics[width=\textwidth]{img/material-gold}
       \caption{Or}
     \end{subfigure}
   \end{figure}

   \begin{figure}[!h]
     \centering
     \captionsetup[subfigure]{labelformat=empty}
     \begin{subfigure}[b]{2cm}
       \includegraphics[width=\textwidth]{img/material-mercury}
       \caption{Mercure}
     \end{subfigure}
     \begin{subfigure}[b]{2cm}
       \includegraphics[width=\textwidth]{img/material-sulfur}
       \caption{Soufre}
     \end{subfigure}
     \begin{subfigure}[b]{2cm}
       $\xrightarrow{\text{transmutation}}$
       \caption{\newline} % latex hacks are teh shit
     \end{subfigure}
     \begin{subfigure}[b]{2cm}
       \includegraphics[width=\textwidth]{img/material-catalyst}
       \caption{Catalyseur}
     \end{subfigure}
   \end{figure}


Vous pouvez transmuter un unique bloc de métal. Néanmoins, cela revient à
détruire ce bout d'élément et donc à perdre de l'or - stratégie aussi
audacieuse que dangereuse.

Catalyser
---------

Lorsque vous possédez une zone suffisamment large de catalyseur (mercure ou
soufre), vous pouvez sublimer ces éléments, les faisant ainsi disparaître de
l'établi. Le catalyseur obtenu vous permettra de transformer un élément
quelconque de l'établi en un autre élément de votre choix.
Plus la zone sublimée est grande, plus vous aurez de catalyseur et plus vous
pourrez transformer de cases.
Transmuter une zone de catalyseurs vous donnera également un peu d'or.
Rien ne vous empêche de catalyser un élément de l'établi d'un autre apprenti,
tant que celui-ci a le dos tourné...

Si vous n'utilisez pas vos catalyseurs ce tour-ci, en entier, ils
se volatiseront et il n'en restera rien au tour suivant.

.. raw:: latex

   \begin{figure}[!h]
     \centering
     \captionsetup[subfigure]{labelformat=empty,position=b}
     \begin{subfigure}[b]{1.5cm}
       \includegraphics[width=\textwidth]{img/material-lead}
       \caption{Plomb}
     \end{subfigure}
     ~
     \begin{subfigure}[b]{1.5cm}
       \includegraphics[width=\textwidth]{img/material-iron}
       \caption{Fer}
     \end{subfigure}
     ~
     \begin{subfigure}[b]{1.5cm}
       \includegraphics[width=\textwidth]{img/material-copper}
       \caption{Cuivre}
     \end{subfigure}
     ~
     \begin{subfigure}[b]{1.5cm}
       \includegraphics[width=\textwidth]{img/material-sulfur}
       \caption{Soufre}
     \end{subfigure}
     ~
     \begin{subfigure}[b]{1.5cm}
       \includegraphics[width=\textwidth]{img/material-mercury}
       \caption{Mercure}
     \end{subfigure}
     \begin{subfigure}[b]{1.5cm}
     \begin{tikzpicture}
       % $\xrightarrow{\text{catalyse}}$
       % \caption{\newline} % latex hacks are teh shit
       \node[] (image) at (0,0) {\includegraphics[width=.8cm]{img/material-catalyst}};
       \node[] at (0,.8) {\footnotesize catalyse};
       \draw[->] (-.7,.5) -- (.7,.5);
     \end{tikzpicture}
     \end{subfigure}
     \begin{subfigure}[b]{1.5cm}
       \includegraphics[width=\textwidth]{img/material-other}
       \caption{Élément}
     \end{subfigure}
   \end{figure}

Score
=====

Votre score est déterminé par la quantité d'or que vous serez parvenu à
transmuter en ``NB_TOURS``.