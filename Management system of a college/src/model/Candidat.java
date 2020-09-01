package model;

public class Candidat {
    private String numeCandidat;
    private String CNPCandidat;
    private double notaBac;
    private double notaAdmitere;

    public Candidat(String numeCandidat, String CNPCandidat, double notaBac) {
        this.numeCandidat = numeCandidat;
        this.CNPCandidat = CNPCandidat;
        if(notaBac >= 10){
            this.notaBac = 10.00;
        }
        else {
            this.notaBac = notaBac;
        }
        this.notaAdmitere = 0;
    }

    public String getNumeCandidat() {
        return numeCandidat;
    }

    public void setNumeCandidat(String numeCandidat) {
        this.numeCandidat = numeCandidat;
    }

    public String getCNPCandidat() {
        return CNPCandidat;
    }

    public void setCNPCandidat(String CNPCandidat) {
        this.CNPCandidat = CNPCandidat;
    }

    @Override
    public String toString() {
        return "nume: " + numeCandidat + '\t' +
                ", CNP= " + CNPCandidat + '\t' +
                ", Nota Bac = " +  String.format("%.02f",notaBac) +  '\t' +
                ", Nota Admitere = " + String.format("%.02f",notaAdmitere) + '\n';
    }

    public double getNotaBac() {
        return notaBac;
    }

    public void setNotaBac(double notaBac) {
        this.notaBac = notaBac;
    }

    public double getNotaAdmitere() {
        return notaAdmitere;
    }

    public void setNotaAdmitere(double notaAdmitere) {
        this.notaAdmitere = notaAdmitere;
    }

}
