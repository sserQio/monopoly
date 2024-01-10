# monopoly
Versione semplificata del gioco Monopoly da giocare su CLI. 
Progetto finale per Laboratorio di Programmazione a cura di: Barbieri Alberto, Favretto Mattia, Petenazzo Sergio.

L'idea con cui abbiamo sviluppato quest'implementazione era di riuscire a rispettare le condizioni della consegna pur avendo un occhio di riguardo verso la versatilità, proponendo dunque un progetto che fosse predisposto per situazioni anche differenti a quelle specificate, eventualmente con un minimo numero di modifiche. Per questo motivo segnaliamo le seguenti scelte:
    
    La classe Player non è virtuale pura, ma classe base che rappresenta un giocatore che ad ogni possibilità effettua l'eventuale acquisto/upgrade. CPUPlayer e HumanPlayer sono derivate di Player che rispettano le indicazioni date dalla consegna.

    Le mosse e le decisioni le effettua la classe Player (o le derivate), ma è la classe Board, rappresentante il tabellone di gioco, a stabilire tutte le regole di gioco. 
    Le classi dei giocatori vogliono quindi essere indipendenti dal tabellone su cui giocano, se non per quanto riguarda la funzione di movimento che è chiaramente legata alla struttura del tabellone.

    In Board il costruttore è predisposto per soli 4 giocatori, come da consegna, ma con lievi modifiche è possibile modificare il numero senza danneggiare il progetto di gioco, che vuole essere indipendente dal numero di giocatori. Stesso discorso vale per le tipologie di caselle: volendone aggiungere, sarà sufficiente modificare la relativa lista nell'header e aggiungere un else if in fill_board

