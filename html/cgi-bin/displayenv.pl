#!/usr/bin/env perl

print "<!DOCTYPE html>\n";
print "<html>\n";
print "<head>\n";
print "<meta charset='UTF-8'>\n";
print "<title>Variables d'environnement</title>\n";
print "</head>\n";
print "<body>\n";
print "<h1>Voici les variables d'environnement envoyées au CGI : </h1>\n";

foreach $key (sort(keys %ENV)) {
  print "<strong>$key</strong> = $ENV{$key}<br>\n";
}
print "</body>\n";
print "</html>\n";
