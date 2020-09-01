package contracts;

import model.Candidat;

public interface FacultateContract {
    Candidat[] adaugaCandidat(Candidat candidat);
    Candidat[] stergeCandidat(String cnp);
    void examinare(Candidat candidat);

}
