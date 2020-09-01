package model;

import contracts.CandidatComparator;
import contracts.FacultateContract;
import model.Candidat;

import java.util.Collections;
import java.util.List;

public abstract class Facultate implements FacultateContract {
    protected String numeFacultate;
    protected String locatieFacultate;
    protected int numarLocuri;
    protected int numarLocuriDisponibile;

    protected Candidat[] candidati;
    protected List<Candidat> candidatiAdmisi;
    protected List<Candidat> candidatiRespinsi;

    public abstract double evaluare(Candidat candidat);

    public boolean notaValida(double nota) {
        if (nota >= 5 && nota <= 10) {
            return true;
        }
        return false;
    }

    public void examinare(Candidat candidat) {
        candidat.setNotaAdmitere(evaluare(candidat));
        if(notaValida(candidat.getNotaAdmitere())) {
            candidatiAdmisi.add(candidat);
        }
        else {
            candidatiRespinsi.add(candidat);
        }
        Collections.sort(candidatiAdmisi, new CandidatComparator());
        if(candidatiAdmisi.size() > numarLocuri) {
            for(int i = candidatiAdmisi.size() - numarLocuri; i < candidatiAdmisi.size(); i++) {
                candidatiRespinsi.add(candidatiAdmisi.get(i));
                candidatiAdmisi.remove(i);
            }
        }
    }

    public String getNumeFacultate() {
        return numeFacultate;
    }

    public void setNumeFacultate(String numeFacultate) {
        this.numeFacultate = numeFacultate;
    }

    public String getLocatieFacultate() {
        return locatieFacultate;
    }

    public void setLocatieFacultate(String locatieFacultate) {
        this.locatieFacultate = locatieFacultate;
    }

    public int getNumarLocuri() {
        return numarLocuri;
    }

    public void setNumarLocuri(int numarLocuri) {
        this.numarLocuri = numarLocuri;
    }

    public List<Candidat> getCandidatiAdmisi() {
        return candidatiAdmisi;
    }

    public void setCandidatiAdmisi(List<Candidat> candidatiAdmisi) {
        this.candidatiAdmisi = candidatiAdmisi;
    }

    public List<Candidat> getCandidatiRespinsi() {
        return candidatiRespinsi;
    }

    public void setCandidatiRespinsi(List<Candidat> candidatiRespinsi) {
        this.candidatiRespinsi = candidatiRespinsi;
    }

    public Candidat[] getCandidati() {
        return candidati;
    }

    public void setCandidati(Candidat[] candidati) {
        this.candidati = candidati;
    }

    public void afisareCandidati() {
        for (Candidat aux : candidati) {
            System.out.println(aux);
        }
    }

    public int getNumarLocuriDisponibile() {
        return numarLocuriDisponibile;
    }

    public void setNumarLocuriDisponibile(int numarLocuriDisponibile) {
        this.numarLocuriDisponibile = numarLocuriDisponibile;
    }

    public void ordoneazaCandidatiAdmisi(){
        Collections.sort(candidatiAdmisi, new CandidatComparator());
    }
}