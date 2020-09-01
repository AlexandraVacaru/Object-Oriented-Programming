package model;

import contracts.FacultateContract;

import java.util.ArrayList;
import java.util.Random;

public class Matematica extends Facultate implements FacultateContract {

    public Matematica() {
        setNumeFacultate("Facultatea de Matematica");
        setLocatieFacultate("Universitate, Bucuresti, Romania");
        setNumarLocuri(200);
        setNumarLocuriDisponibile(200);
        setCandidati(new Candidat[0]);
        setCandidatiAdmisi(new ArrayList<>());
        setCandidatiRespinsi(new ArrayList<>());
    }

    @Override
    public double evaluare(Candidat candidat) {
        double nota_examen = new Random().nextDouble();
        nota_examen = 1 + nota_examen * 9;
        System.out.println("Nota examen Matematica: " + String.format("%.02f", nota_examen));
        double nota_admitere = (0.5 * candidat.getNotaBac() + 0.5 * nota_examen);
        return nota_admitere;
    }

    @Override
    public Candidat[] adaugaCandidat(Candidat candidat) {

        if( numarLocuri - numarLocuriDisponibile >= 0) {
            Candidat[] tmp = new Candidat[candidati.length + 1];
            System.arraycopy(candidati, 0, tmp, 0, candidati.length);
            tmp[tmp.length - 1] = candidat;
            numarLocuriDisponibile--;
            System.out.println("===== Am adaugat candidatul cu numele: " + candidat.getNumeCandidat() + "=====");
            return tmp;
        }
        else {
            System.out.println("Nu mai sunt locuri disponibile!");
            return candidati;
        }
    }

    @Override
    public Candidat[] stergeCandidat(String cnp) {
        if (candidati.length == 0) {
            System.out.println("Nu exista candidati adaugati!");
            return new Candidat[0];
        } else {
            Candidat[] tmp = new Candidat[candidati.length - 1];
            int j = 0;
            for (int i = 0; i < candidati.length; i++) {
                if (!candidati[i].getCNPCandidat().equals(cnp)) {
                    if (j < tmp.length) {
                        tmp[j] = candidati[i];
                    }
                    j++;
                }
            }

            if (j == candidati.length) {
                System.out.println("Nu exista candidatul cu CNP-ul " + cnp + "!");
                return candidati;
            } else {
                System.out.println("Am eliminat candidatul cu CNP-ul: " + cnp + " !");
                for (int i = 0; i < candidatiAdmisi.size(); i++) {
                    if (candidatiAdmisi.get(i).getCNPCandidat().equals(cnp)) {
                        candidatiAdmisi.remove(i);
                        System.out.println("Candidatul era admis!");
                    }
                }
                for (int i = 0; i < candidatiRespinsi.size(); i++) {
                    if (candidatiRespinsi.get(i).getCNPCandidat().equals(cnp)) {
                        candidatiRespinsi.remove(i);
                        System.out.println("Candidatul era respins!");
                    }
                }
                return tmp;
            }
        }
    }
}
