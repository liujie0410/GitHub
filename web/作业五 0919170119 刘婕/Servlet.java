
import javax.servlet.annotation.*;
import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(name = "Servlet", urlPatterns = "/Servlet")
public class Servlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
       //浏览器能正确显示中文
        response.setCharacterEncoding("GBK");
       //获取对象
        ServletContext application =this.getServletContext();
        Integer count = (Integer) application.getAttribute("count");
        if(count==null)
        {
          application.setAttribute("count", 1);
        }else{
          application.setAttribute("count", count+1);
        }
       //向浏览器输出，需要使用响应请求
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<h2>该servlet页面已被访问了 "+count+" 次</h2>");

    }
}
