<%--
  Created by IntelliJ IDEA.
  User: liujie
  Date: 2019-11-09
  Time: 16:34
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
  <head>
    <title>HelloWorld</title>
  </head>
  <body>
  <%
    //获取counter的值，生命周期从打开web开始，到关闭web
    Object obj =application.getAttribute("counter");
    if(obj==null){
      application.setAttribute("counter", new Integer(1));
      out.print("该页面已被访问1次！");
    }else{
      int count=Integer.parseInt(obj.toString());
      count++;
      out.print("该页面已被访问了"+count+"次！");
      application.setAttribute("counter", count);
    }
  %>
  </body>
</html>
