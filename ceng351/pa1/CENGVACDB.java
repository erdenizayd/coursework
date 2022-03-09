package ceng.ceng351.cengvacdb;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;

public class CENGVACDB implements ICENGVACDB{
    private static String user = "e2380103"; // TODO: Your userName
    private static String password = "JCz?@E#0I3Zf"; //  TODO: Your password
    private static String host = "144.122.71.121"; // host name
    private static String database = "db2380103"; // TODO: Your database name
    private static int port = 8080; // port

    private static Connection connection = null;

    @Override
    public void initialize() {
        String url = "jdbc:mysql://" + host + ":" + port + "/" + database;

        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection(url,user,password);
        }
        catch (SQLException | ClassNotFoundException e){
            e.printStackTrace();
        }
    }

    @Override
    public int createTables() {
        int count = 0;

        String createUser = "create table user (" +
                "userID int not null," +
                "userName varchar(30)," +
                "age int," +
                "address varchar(150)," +
                "password varchar(30)," +
                "status varchar(15)," +
                "primary key (userID))";

        String createVaccine = "create table vaccine (" +
                "code int," +
                "vaccinename varchar(30)," +
                "type varchar(30)," +
                "primary key (code))";

        String createVaccination = "create table vaccination (" +
                "code int," +
                "userID int," +
                "dose int,"  +
                "vacdate date," +
                "primary key (code, userID, dose)," +
                "foreign key (code) references vaccine(code) on delete cascade on update cascade," +
                "foreign key (userID) references user(userID))";

        String createAllergicSideEffect = "create table allergicsideeffect (" +
                "effectcode int," +
                "effectname varchar(50)," +
                "primary key (effectcode))";

        String createSeen = "create table seen (" +
                "effectcode int," +
                "code int," +
                "userID int," +
                "date date," +
                "degree varchar(30)," +
                "primary key (effectcode, code, userID)," +
                "foreign key (effectcode) references allergicsideeffect(effectcode)," +
                "foreign key (code) references vaccine(code) on delete cascade on update cascade," +
                "foreign key (userID) references user(userID))";

        try {
            Statement statement = this.connection.createStatement();

            statement.executeUpdate(createUser);
            count++;

            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        try {
            Statement statement = this.connection.createStatement();

            statement.executeUpdate(createVaccine);
            count++;

            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        try {
            Statement statement = this.connection.createStatement();

            statement.executeUpdate(createVaccination);
            count++;

            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        try {
            Statement statement = this.connection.createStatement();

            statement.executeUpdate(createAllergicSideEffect);
            count++;

            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        try {
            Statement statement = this.connection.createStatement();

            statement.executeUpdate(createSeen);
            count++;

            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return count;
    }

    @Override
    public int dropTables() {
        int count = 0;
        String dropUser = "drop table if exists user";
        String dropVaccine = "drop table if exists vaccine";
        String dropVaccination = "drop table if exists vaccination";
        String dropAllergicSideEffect = "drop table if exists allergicsideeffect";
        String dropSeen = "drop table if exists seen";

        try {
            Statement statement = connection.createStatement();

            statement.executeUpdate(dropSeen);
            count++;

            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        try {
            Statement statement = connection.createStatement();

            statement.executeUpdate(dropVaccination);
            count++;

            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        try {
            Statement statement = connection.createStatement();

            statement.executeUpdate(dropUser);
            count++;

            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        try {
            Statement statement = connection.createStatement();

            statement.executeUpdate(dropVaccine);
            count++;

            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        try {
            Statement statement = connection.createStatement();

            statement.executeUpdate(dropAllergicSideEffect);
            count++;

            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }



        return count;
    }

    @Override
    public int insertUser(User[] users) {
        int count = 0;

        for(int i = 0; i < users.length; i++){
            String insert = "insert into user values(" +
                    users[i].getUserID() + ",\"" +
                    users[i].getUserName() + "\"," +
                    users[i].getAge() + ",\"" +
                    users[i].getAddress() + "\",\"" +
                    users[i].getPassword() + "\",\"" +
                    users[i].getStatus() + "\")";

            try{
                Statement statement = connection.createStatement();
                statement.executeUpdate(insert);
                count++;
                statement.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }


        return count;
    }

    @Override
    public int insertAllergicSideEffect(AllergicSideEffect[] sideEffects) {
        int count = 0;

        for(int i = 0; i < sideEffects.length; i++){
            String insert = "insert into allergicsideeffect values(" +
                    sideEffects[i].getEffectCode() + ",\"" +
                    sideEffects[i].getEffectName() + "\")";

            try{
                Statement statement = connection.createStatement();
                statement.executeUpdate(insert);
                count++;
                statement.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }


        return count;
    }

    @Override
    public int insertVaccine(Vaccine[] vaccines) {
        int count = 0;

        for(int i = 0; i < vaccines.length; i++){
            String insert = "insert into vaccine values(" +
                    vaccines[i].getCode() + ",\"" +
                    vaccines[i].getVaccineName() + "\",\"" +
                    vaccines[i].getType() + "\")";

            try{
                Statement statement = connection.createStatement();
                statement.executeUpdate(insert);
                count++;
                statement.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }


        return count;
    }

    @Override
    public int insertVaccination(Vaccination[] vaccinations) {
        int count = 0;

        for(int i = 0; i < vaccinations.length; i++){
            String insert = "insert into vaccination values(" +
                    vaccinations[i].getCode() + "," +
                    vaccinations[i].getUserID() + "," +
                    vaccinations[i].getDose() + ",\"" +
                    vaccinations[i].getVacdate() + "\")";

            try{
                Statement statement = connection.createStatement();
                statement.executeUpdate(insert);
                count++;
                statement.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }


        return count;
    }

    @Override
    public int insertSeen(Seen[] seens) {
        int count = 0;

        for(int i = 0; i < seens.length; i++){
            String insert = "insert into seen values(" +
                    seens[i].getEffectcode() + "," +
                    seens[i].getCode() + "," +
                    seens[i].getUserID() + ",\"" +
                    seens[i].getDate() + "\",\"" +
                    seens[i].getDegree() + "\")";

            try{
                Statement statement = connection.createStatement();
                statement.executeUpdate(insert);
                count++;
                statement.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }


        return count;
    }

    @Override
    public Vaccine[] getVaccinesNotAppliedAnyUser() {
        ResultSet resultSet;
        ArrayList<Vaccine> temp = new ArrayList<>();

        String getVaccines = "select v.code, v.vaccinename, v.type from vaccine v where v.code not in (select vc.code from vaccination vc) order by v.code;";

        try {
            Statement statement = connection.createStatement();
            resultSet = statement.executeQuery(getVaccines);

            while(resultSet.next()) {
                Vaccine row = new Vaccine(resultSet.getInt("code"),
                        resultSet.getString("vaccinename"),
                        resultSet.getString("type"));
                temp.add(row);
            }
        }
        catch (SQLException e) {
            e.printStackTrace();
        }

        Vaccine[] vac = new Vaccine[temp.size()];

        return temp.toArray(vac);
    }

    @Override
    public QueryResult.UserIDuserNameAddressResult[] getVaccinatedUsersforTwoDosesByDate(String vacdate) {
        ResultSet resultSet;
        ArrayList<QueryResult.UserIDuserNameAddressResult> temp = new ArrayList<>();

        String getUsers = "select U.userID, U.userName, U.address from user U where 2 = (select count(*) from vaccination V where V.userID = U.userID and V.vacdate >\"" + vacdate + "\");";

        try {
            Statement statement = connection.createStatement();
            resultSet = statement.executeQuery(getUsers);

            while(resultSet.next()) {
                QueryResult.UserIDuserNameAddressResult row =
                        new QueryResult.UserIDuserNameAddressResult(resultSet.getInt("userID"),
                        resultSet.getString("userName"),
                        resultSet.getString("address"));
                temp.add(row);
            }
            statement.close();
        }
        catch (SQLException e) {
            e.printStackTrace();
        }

        QueryResult.UserIDuserNameAddressResult[] users = new QueryResult.UserIDuserNameAddressResult[temp.size()];

        return temp.toArray(users);
    }

    @Override
    public Vaccine[] getTwoRecentVaccinesDoNotContainVac() {
        ResultSet resultSet;
        Vaccine[] result;
        result = new Vaccine[2];

        String getVacs = "select v.code, vv.vaccinename, vv.type from vaccination v, vaccine vv where v.code = vv.code and  v.code not in (select vc.code from vaccine vc where vc.vaccinename like \"%vac%\") order by vacdate desc";

        try {
            Statement statement = connection.createStatement();
            resultSet = statement.executeQuery(getVacs);
            resultSet.next();
            Vaccine row = new Vaccine(Integer.parseInt(resultSet.getString("code")), resultSet.getString("vaccinename"), resultSet.getString("type"));
            result[0] = row;

            while(resultSet.next()){
                if(resultSet.getInt("code") != result[0].getCode()){
                    Vaccine row2 = new Vaccine(resultSet.getInt("code"), resultSet.getString("vaccinename"), resultSet.getString("type"));
                    result[1] = row2;
                    break;
                }
            }

        }
        catch (SQLException e){
            e.printStackTrace();
        }

        return result;
    }

    @Override
    public QueryResult.UserIDuserNameAddressResult[] getUsersAtHasLeastTwoDoseAtMostOneSideEffect() {
        ResultSet resultSet;
        ArrayList<QueryResult.UserIDuserNameAddressResult> temp = new ArrayList<>();

        String getUsers = "select u.userID, u.userName, u.address from user u where 2 <= (select count(*) from vaccination v where v.userID = u.userID) and 1 >= (select count(*) from seen s where s.userID = u.userID) order by userID asc;";

        try {
            Statement statement = connection.createStatement();
            resultSet = statement.executeQuery(getUsers);

            while(resultSet.next()) {
                QueryResult.UserIDuserNameAddressResult row =
                        new QueryResult.UserIDuserNameAddressResult(resultSet.getInt("userID"),
                                resultSet.getString("userName"),
                                resultSet.getString("address"));
                temp.add(row);
            }
            statement.close();
        }
        catch (SQLException e) {
            e.printStackTrace();
        }

        QueryResult.UserIDuserNameAddressResult[] users = new QueryResult.UserIDuserNameAddressResult[temp.size()];

        return temp.toArray(users);
    }

    @Override
    public QueryResult.UserIDuserNameAddressResult[] getVaccinatedUsersWithAllVaccinesCanCauseGivenSideEffect(String effectname) {
        ResultSet resultSet;
        ArrayList<QueryResult.UserIDuserNameAddressResult> temp = new ArrayList<>();

        String getUsers = "select u.userID, u.userName, u.address from user u where not exists(select s.code from seen s, allergicsideeffect a where s.effectcode = a.effectcode and a.effectname = \"" + effectname + "\"and not exists (select vc.code from vaccination vc where vc.userID = u.userID and s.code = vc.code)) order by userID asc;";

        try {
            Statement statement = connection.createStatement();
            resultSet = statement.executeQuery(getUsers);

            while(resultSet.next()) {
                QueryResult.UserIDuserNameAddressResult row =
                        new QueryResult.UserIDuserNameAddressResult(resultSet.getInt("userID"),
                                resultSet.getString("userName"),
                                resultSet.getString("address"));
                temp.add(row);
            }
            statement.close();
        }
        catch (SQLException e) {
            e.printStackTrace();
        }

        QueryResult.UserIDuserNameAddressResult[] users = new QueryResult.UserIDuserNameAddressResult[temp.size()];

        return temp.toArray(users);
    }

    @Override
    public QueryResult.UserIDuserNameAddressResult[] getUsersWithAtLeastTwoDifferentVaccineTypeByGivenInterval(String startdate, String enddate) {
        ResultSet resultSet;
        ArrayList<QueryResult.UserIDuserNameAddressResult> temp = new ArrayList<>();

        String getUsers = "select U.userID, U.userName, U.address from user U where 2 <= (select count(distinct V.code) from vaccination V where V.userID = U.userID and V.vacdate >=\"" + startdate + "\" and V.vacdate <=\"" + enddate + "\") order by userID asc;";

        try {
            Statement statement = connection.createStatement();
            resultSet = statement.executeQuery(getUsers);

            while(resultSet.next()) {
                QueryResult.UserIDuserNameAddressResult row =
                        new QueryResult.UserIDuserNameAddressResult(resultSet.getInt("userID"),
                                resultSet.getString("userName"),
                                resultSet.getString("address"));
                temp.add(row);
            }
            statement.close();
        }
        catch (SQLException e) {
            e.printStackTrace();
        }

        QueryResult.UserIDuserNameAddressResult[] users = new QueryResult.UserIDuserNameAddressResult[temp.size()];

        return temp.toArray(users);
    }

    @Override
    public AllergicSideEffect[] getSideEffectsOfUserWhoHaveTwoDosesInLessThanTwentyDays() {
        ResultSet resultSet;
        ArrayList<AllergicSideEffect> temp = new ArrayList<>();

        String getAllergies = "select a.effectcode, a.effectname from allergicsideeffect a, seen s where exists (select * from vaccination v1, vaccination v2 where v1.userID = v2.userID and datediff(v1.vacdate,v2.vacdate) < 20\n" +
                "and datediff(v1.vacdate,v2.vacdate) > 0 and s.userID = v1.userID and s.effectcode = a.effectcode) order by effectcode asc;";

        try {
            Statement statement = connection.createStatement();
            resultSet = statement.executeQuery(getAllergies);

            while(resultSet.next()) {
                AllergicSideEffect row = new AllergicSideEffect(resultSet.getInt("effectcode"),
                        resultSet.getString("effectname"));
                temp.add(row);
            }
        }
        catch (SQLException e) {
            e.printStackTrace();
        }

        AllergicSideEffect[] side = new AllergicSideEffect[temp.size()];

        return temp.toArray(side);
    }

    @Override
    public double averageNumberofDosesofVaccinatedUserOverSixtyFiveYearsOld() {
        ResultSet resultSet;
        double result = 0;

        String getAvg = "select avg(temp.scount) as average from (select u.userID, count(*) as scount from user u, vaccination v where u.userID = v.userID and u.age > 65 group by u.userID) as temp;";

        try{
            Statement statement = connection.createStatement();
            resultSet = statement.executeQuery(getAvg);

            resultSet.next();
            result = resultSet.getDouble("average");

        }
        catch (SQLException e){
            e.printStackTrace();
        }

        return result;
    }

    @Override
    public int updateStatusToEligible(String givendate) {
        ResultSet resultSet;
        int result = 0;

        String update = "update user set status = \"Eligible\" where userID in (select temp.userID from (select v.userID, max(vacdate) as maxtime from vaccination v group by v.userID) as temp where datediff(\"2021-12-19\",temp.maxtime)> 120) and status = \"Not_Eligible\";";
        String count = "select ROW_COUNT() as count;";

        try{
            Statement statement = connection.createStatement();
            statement.executeUpdate(update);
            resultSet = statement.executeQuery(count);

            resultSet.next();
            result = resultSet.getInt("count");
        }
        catch (SQLException e){
            e.printStackTrace();
        }

        return result;
    }

    @Override
    public Vaccine deleteVaccine(String vaccineName) {
        ResultSet resultSet;
        Vaccine result = null;

        String delete = "delete from vaccine where vaccinename = \"" + vaccineName + "\";";
        String res = "select * from vaccine where vaccinename = \"" + vaccineName + "\";";

        try{
            Statement statement = connection.createStatement();
            resultSet = statement.executeQuery(res);

            resultSet.next();
            result = new Vaccine(resultSet.getInt("code"),resultSet.getString("vaccinename"),resultSet.getString("type"));
        }
        catch (SQLException e){
            e.printStackTrace();
        }


        try{
            Statement statement = connection.createStatement();

            statement.executeUpdate(delete);
            statement.close();
        }
        catch (SQLException e){
            e.printStackTrace();
        }

        return result;
    }
}
