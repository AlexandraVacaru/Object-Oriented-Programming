import model.*;
import service.MainRepository;
import service.MainService;
import service.Meniu;
import threads.MyCallable;

import javax.swing.*;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        Facultate facInformatica = new Informatica();
        Facultate facMatematica = new Matematica();

        MainRepository mainRepository = new MainRepository();


        Scanner scanner = new Scanner(System.in);
        System.out.println("\n");
        System.out.println("Admitere Facultate: " + facInformatica.getNumeFacultate() + " si " +
                facMatematica.getNumeFacultate());
        System.out.println("Doriti sa folositi interfata grafica? Y/N");
        String grafica = scanner.next();
        if (grafica.equals("N")) {

            System.out.println("===================");
            System.out.println("Selectati una dintre optiunile din meniu: ");
            System.out.println("1 - Adauga candidat");
            System.out.println("2 - Sterge candidat");
            System.out.println("3 - Afiseaza toti candidatii");
            System.out.println("4 - Afiseaza candidatii admisi");
            System.out.println("5 - Afiseaza candidatii respinsi");
            System.out.println("6 - Afiseaza candidatii admisi in ordine alfabetica");
            System.out.println("7 - Afiseaza candidatul admis cu nota cea mai mare");
            System.out.println("8 - Scrie in raport toti canditatii");
            System.out.println("9 - Scrie in raport toti candidatii admisi la facultatea de matematica");
            System.out.println("10 - Scrie in raport toti candidatii admisi la facultatea de informatica");
            System.out.println("11 - Scrie in raport toti candidatii respinsi");
            System.out.println("12 - Afiseaza media totala pentru candidatii admisi");
            System.out.println("13 - Terminare");

            while(true) {
                String optiune = scanner.next();
                switch (optiune) {
                    case "1":
                        Meniu.adaugareCandidati(scanner, facInformatica, facMatematica, mainRepository);
                        break;
                    case "2":
                        Meniu.stergereCandidati(scanner, facInformatica, facMatematica, mainRepository);
                        break;
                    case "3":
                        Meniu.afisareCandidati(scanner, facInformatica, facMatematica,mainRepository);
                        break;
                    case "4":
                        Meniu.afisareCandidatiAdmisi(scanner, facInformatica, facMatematica);
                        break;
                    case "5":
                        Meniu.afisareCandidatiRespinsi(scanner, facInformatica, facMatematica);
                        break;
                    case "6":
                        Meniu.afisareCandidatiAlfabetic(scanner, facInformatica, facMatematica);
                        break;
                    case "7":
                        Meniu.afisareMedieMax(scanner, facInformatica, facMatematica);
                        break;
                    case "8":
                        String filePath = "C:\\Users\\emil\\Desktop\\PAO\\proiect pao - partea 1\\src\\repositories" +
                                "\\Report1.csv";
                        MainService.initReportHeader(filePath);
                        try {
                            Class.forName("com.mysql.jdbc.Driver");
                            for(Candidat i : mainRepository.getPeopleMate()) {
                                MainService.scrieRaportCanditati(i,filePath, "Matematica");
                            }
                            for(Candidat i : mainRepository.getPeopleInfo()) {
                                MainService.scrieRaportCanditati(i,filePath, "Informatica");
                            }
                        }
                        catch (ClassNotFoundException | SQLException e) {
                            e.printStackTrace();
                        }

                        System.out.println("Raport generat cu succes! Vezi Report1.csv" );
                        break;
                    case "9":
                        filePath = "C:\\Users\\emil\\Desktop\\PAO\\proiect pao - partea 1\\src\\repositories\\Report2.csv";
                        MainService.initReportHeader(filePath);
                        try {
                            Class.forName("com.mysql.jdbc.Driver");
                            for(Candidat i: mainRepository.getPeopleMate()) {
                                if (i.getNotaAdmitere() >= 5) {
                                    MainService.scrieRaportCanditati(i, filePath, "Matematica");
                                }
                            }
                        }
                        catch (ClassNotFoundException | SQLException e) {
                            e.printStackTrace();
                        }

                        System.out.println("Raport generat cu succes! Vezi Report2.csv");
                        break;
                    case "10":
                        filePath = "C:\\Users\\emil\\Desktop\\PAO\\proiect pao - partea 1\\src\\repositories\\Report3.csv";
                        MainService.initReportHeader(filePath);
                        try {
                            Class.forName("com.mysql.jdbc.Driver");
                            for(Candidat i: mainRepository.getPeopleInfo()) {
                                if (i.getNotaAdmitere() >= 5) {
                                    MainService.scrieRaportCanditati(i, filePath, "Informatica");
                                }
                            }
                        }
                        catch (ClassNotFoundException | SQLException e) {
                            e.printStackTrace();
                        }
                        System.out.println("Raport generat cu succes! Vezi Report3.csv");
                        break;
                    case "11":
                        filePath = "C:\\Users\\emil\\Desktop\\PAO\\proiect pao - partea 1\\src\\repositories\\Report4.csv";
                        MainService.initReportHeader(filePath);
                        try {
                            Class.forName("com.mysql.jdbc.Driver");
                            for(Candidat i : mainRepository.getPeopleMate()) {
                                if (i.getNotaAdmitere() < 5) {
                                    MainService.scrieRaportCanditati(i, filePath, "Matematica");
                                }
                            }
                            for(Candidat i : mainRepository.getPeopleInfo()) {
                                if (i.getNotaAdmitere() < 5) {
                                    MainService.scrieRaportCanditati(i, filePath, "Informatica");
                                }
                            }
                        }
                        catch (ClassNotFoundException | SQLException e) {
                            e.printStackTrace();
                        }
                        System.out.println("Raport generat cu succes! Vezi Report4.csv");
                        break;
                    case "12":
                        double[] noteMate = new double[0];
                        double[] noteInfo = new double[0];
                        try {
                            Class.forName("com.mysql.jdbc.Driver");
                            noteMate = new double[mainRepository.getPeopleMate().size()];
                            noteInfo = new double[mainRepository.getPeopleInfo().size()];

                        }
                        catch (ClassNotFoundException | SQLException e) {
                            e.printStackTrace();
                        }

                        try {
                            Class.forName("com.mysql.jdbc.Driver");
                            int i = 0;
                            for(Candidat candidat : mainRepository.getPeopleMate()) {
                                if (candidat.getNotaAdmitere() > 5) {
                                    noteMate[i] = candidat.getNotaAdmitere();
                                    i++;
                                }
                            }
                            i = 0;
                            for(Candidat candidat : mainRepository.getPeopleInfo()) {
                                if (candidat.getNotaAdmitere() > 5) {
                                    noteInfo[i] = candidat.getNotaAdmitere();
                                    i++;
                                }
                            }
                        }
                        catch (ClassNotFoundException | SQLException e) {
                            e.printStackTrace();
                        }
                        ExecutorService executorService = Executors.newFixedThreadPool(5);

                        MyCallable m1 = new MyCallable(noteMate);
                        MyCallable m2 = new MyCallable(noteInfo);
                        List<Future<Double>> ftResult = executorService.invokeAll(Arrays.asList(m1,m2));
                        double callableSum = ftResult.stream().mapToDouble(result -> {
                            try {
                                return result.get();
                            } catch (InterruptedException e) {
                                e.printStackTrace();
                            } catch (ExecutionException e) {
                                e.printStackTrace();
                            }
                            throw  new RuntimeException("ERROR ON CALCULATION!!");
                        }).sum();

                        System.out.println("Media admitere: " + String.format("%.2f", callableSum/2));
                        break;
                    case "13":
                        System.exit(0);
                        break;
                    default:
                        System.out.println("\n");
                        System.out.println("Ai ales o optiune incorecta!");
                }
            }
        }

        if (grafica.equals("Y")) {

            JFrame jFrame = new JFrame("Add new person");

            JLabel nameLabel = new JLabel("Nume: ");
            JTextField nameTextField = new JTextField();
            nameLabel.setBounds(10, 50, 200, 30);
            nameTextField.setBounds(65, 50, 200, 30);

            JLabel cnpLabel = new JLabel("CNP: ");
            JTextField cnpTextField = new JTextField();
            cnpLabel.setBounds(10, 100, 200, 30);
            cnpTextField.setBounds(65, 100, 200, 30);

            JLabel notaLabel = new JLabel("Nota Bac: ");
            JTextField notaTextField = new JTextField();
            notaLabel.setBounds(10, 150, 200, 30);
            notaTextField.setBounds(70, 150, 200, 30);

            JLabel facultateLabel = new JLabel("Facultate: ");
            JTextField facultateTextField = new JTextField();
            facultateLabel.setBounds(10, 200, 200, 30);
            facultateTextField.setBounds(70, 200, 200, 30);

            JButton jButtonAdd = new JButton("Save Person");
            jButtonAdd.setBounds(350, 200, 150, 30);

            JLabel titluTabelMate = new JLabel("Candidatii de la matematica:");
            titluTabelMate.setBounds(50, 240, 200, 30);
            JList<Candidat> jListMate = new JList<>();
            jListMate.setBounds(50, 270, 500, 200);

            try {
                Class.forName("com.mysql.jdbc.Driver");
                jListMate.setListData(mainRepository.getPeopleMate().toArray(new Candidat[0]));
            } catch (ClassNotFoundException | SQLException e) {
                e.printStackTrace();
            }

            JLabel titluTabelInfo = new JLabel("Candidatii de la informatica:");
            titluTabelInfo.setBounds(50, 480, 200, 30);
            JList<Candidat> jListInfo = new JList<>();
            jListInfo.setBounds(50, 510, 500, 200);

            try {
                Class.forName("com.mysql.jdbc.Driver");
                jListInfo.setListData(mainRepository.getPeopleInfo().toArray(new Candidat[0]));
            } catch (ClassNotFoundException | SQLException e) {
                e.printStackTrace();
            }

            jButtonAdd.addActionListener(Meniu.addActionListener(nameTextField, cnpTextField, notaTextField,
                    facultateTextField, jListMate, jListInfo, facInformatica, facMatematica, mainRepository));


            JButton deletePersonButtonMate = new JButton("Delete person");
            deletePersonButtonMate.setBounds(570, 300, 150, 30);
            deletePersonButtonMate.addActionListener(Meniu.deletePersonActionListenerMate(jListMate, facMatematica,
                    mainRepository));

            JButton deletePersonButtonInfo = new JButton("Delete person");
            deletePersonButtonInfo.setBounds(570, 530, 150, 30);
            deletePersonButtonInfo.addActionListener(Meniu.deletePersonActionListenerInfo(jListInfo, facInformatica,
                    mainRepository));

            jFrame.add(nameLabel);
            jFrame.add(nameTextField);
            jFrame.add(cnpLabel);
            jFrame.add(cnpTextField);
            jFrame.add(notaLabel);
            jFrame.add(notaTextField);
            jFrame.add(facultateLabel);
            jFrame.add(facultateTextField);
            jFrame.add(jButtonAdd);
            jFrame.add(titluTabelMate);
            jFrame.add(jListMate);
            jFrame.add(deletePersonButtonMate);
            jFrame.add(titluTabelInfo);
            jFrame.add(jListInfo);
            jFrame.add(deletePersonButtonInfo);

            jFrame.setSize(800, 800);
            jFrame.setLayout(null);
            jFrame.setVisible(true);

        }


    }
}
