import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

/**
 * A sample program that demonstrates how to execute SQL INSERT statement
 * using JDBC. 
 * @author www.codejava.net
 *
 */
public class Jdbc_homework1_2 {

	public static void main(String[] args) {
		String dbURL = "jdbc:mysql://localhost:3306/sample";
		String username = "root";
		String password = "0416";
		
		try {
			Connection conn = DriverManager.getConnection(dbURL, username, password);
			String sql = "INSERT INTO student (id, name, major_id) VALUES (?, ?, ?)";
			
			PreparedStatement statement = conn.prepareStatement(sql);
			statement.setString(1, "2012004021");
			statement.setString(2, "½É±Ô¹Î");
			statement.setString(3, "5");
			
			int rowsInserted = statement.executeUpdate();
			if (rowsInserted > 0) {
				System.out.println("A new user was inserted successfully!");
			}

			
		} catch (SQLException ex) {
			ex.printStackTrace();
		}		
	}
}