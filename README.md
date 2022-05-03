# Projet Demineur : Manuel de mise en marche

# Charger le projet :
<pre><code>make all
export LD_LIBRARY_PATH=$PWD/lib
./demineur
</code></pre>

# Jouer un test unitaire :
<pre><code>./test/TU_XXX
</code></pre>

# Nettoyer votre répertoire :
<pre><code>make clean
</code></pre>

# Générer une documentation Latec & HTML :
<pre><code>make doc
</code></pre>

# Consulter la documentation :
doc -> html > index.html

# Fonctionalités implémentées :
- Jeu du demineur complet avec grille et nombre de mine modulable.
- Jeu du demineur par l'ordinateur possiblité de choisir un nombre de partie par strategie et de moduler la taille de la grille/nombre de mine.
Un tableau de statistique s'affiche alors sur les performances de chaques stratégies.

