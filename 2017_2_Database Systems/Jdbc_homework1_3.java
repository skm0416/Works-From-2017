import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

/**
 * A sample program that demonstrates how to execute SQL DELETE statement
 * using JDBC. 
 * @author www.codejava.net
 *
 */
public class Jdbc_homework1_3 {

	public static void main(String[] args) {
		String dbURL = "jdbc:mysql://127.0.0.1:3306/sample";
		String username = "root";
		String password = "0416";
		
		try {

			Connection conn = DriverManager.getConnection(dbURL, username, password);
			String sql = "DELETE FROM course WHERE credit=3";
			
			PreparedStatement statement = conn.prepareStatement(sql);
			
			int rowsDeleted = statement.executeUpdate();
			if (rowsDeleted > 0) {
				System.out.println(rowsDeleted + " course were deleted successfully!");
			}
		} catch (SQLException ex) {
			ex.printStackTrace();
		}		
	}
}