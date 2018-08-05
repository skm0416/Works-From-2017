import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

/**
 * A sample program that demonstrates how to execute SQL SELECT statement
 * using JDBC. 
 * @author www.codejava.net
 *
 */
public class Jdbc_homework1_1 {

	public static void main(String[] args) {
		String dbURL = "jdbc:mysql://localhost:3306/sample";
		String username = "root";
		String password = "0416";
		
		try  {
			Connection conn = DriverManager.getConnection(dbURL, username, password);
			String sql = "SELECT * FROM building WHERE rooms>19";
			
			Statement statement = conn.createStatement();
			ResultSet result = statement.executeQuery(sql);
			
			int count = 0;
			
			while (result.next()){
				String name = result.getString(2);
				String admin = result.getString(3);
				String rooms = result.getString(4);
				
				String output = "Building #%d: %s - %s - %s";
				System.out.println(String.format(output, ++count, name, admin,rooms));
			}
			
		} catch (SQLException ex) {
			ex.printStackTrace();
		}		
	}
}