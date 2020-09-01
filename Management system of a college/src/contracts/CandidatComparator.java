package contracts;

import model.Candidat;

import java.util.Comparator;

public class CandidatComparator implements Comparator<Candidat> {

    @Override
    public int compare(Candidat c1, Candidat c2) {
        return (int) (c2.getNotaAdmitere() - c1.getNotaAdmitere());

    }
}
