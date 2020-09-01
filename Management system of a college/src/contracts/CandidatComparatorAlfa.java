package contracts;

import model.Candidat;

import java.util.Comparator;

public class CandidatComparatorAlfa implements Comparator<Candidat> {
    @Override
    public int compare(Candidat c1, Candidat c2) {
        return (c1.getNumeCandidat().compareTo(c2.getNumeCandidat()));
    }

}
